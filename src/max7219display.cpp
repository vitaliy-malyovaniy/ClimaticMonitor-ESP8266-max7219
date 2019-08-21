#include "max7219display.h"
#include "sensorsBME280.h"

LedControl lc(13,14,12,1);
extern TickerScheduler ts;

void max7219displayInit(void){
    // Initialize the MAX7219 
    // Serial.println("Initialize the MAX7219...");
    lc.shutdown(0,false); // To Enable the Display 
    lc.setIntensity(0,15); // To set the brightness level (0 is min, 15 is max) 
    lc.clearDisplay(0); // To Clear the display register 
     ts.add(1, 2550, [&](void*){
        show ();
     }, nullptr, true);
}

void show (){
    static int i = 1;
    switch (i){
        case 1: printTwoNumb(eCO2, 3, false);
                printSymbolCO();
                break;
        case 2: printTwoNumb(BMEtempC, 3, true);
                printSymbolTermo();
                break;  
        }
    i++;
    if (i==3) i=1;
};

void printTwoNumb(float value_t, int position, bool point){
    int value;

    if (value_t > 100) {
        value = value_t;
    }else{
        value = value_t*10;
    }
    
    int numInPos1, numInPos2, numInPos3, numInPos4; 
     numInPos1 = value%10;
     numInPos2 = ((value%100)-numInPos1)/10;
     numInPos3 = ((value%1000)-numInPos2)/100;
     numInPos4 = ((value%10000)-numInPos2)/1000;
    //  Serial.print("numInPos4: ");
    //  Serial.println(numInPos4);
     lc.clearDisplay(0); 
    lc.setDigit(0,position,numInPos1, false);
    lc.setDigit(0,position+2,numInPos3, false);
    lc.setDigit(0,position+1,numInPos2, point);
  
    if(!numInPos4){
        lc.setRow(0,position+3,B00000000);
    }else{
        lc.setDigit(0,position+3,numInPos4, false);
    }
}

void printSymbolTermo(){
 lc.setRow(0,1,B01001110); // "С"
 lc.setRow(0,2,B01100011); // символ градус
} 

// void printSymbolCO(){
//  lc.setRow(0,2,B01100111); // "P"
//  lc.setRow(0,3,B01100111); 
// } 
void printSymbolCO(){
 lc.setRow(0,2,B00001101); // "c"
 lc.setRow(0,1,B00011101); // 'o'
} 

void printSymbolPress(){
 lc.setRow(0,2,B00000101); // "r"
 lc.setRow(0,1,B0001111);  // 't'
}
 
// 01000000 - a
// 00100000 - b
// 00001000 - d
// 00000010 - f
