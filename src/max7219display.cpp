#include "max7219display.h"
#include "sensorsBME280.h"

LedControl lc(13,14,12,1);
extern TickerScheduler ts;

void max7219displayInit(void){
    // Initialize the MAX7219 
    Serial.println("Initialize the MAX7219...");
    lc.shutdown(0,false); // To Enable the Display 
    lc.setIntensity(0,15); // To set the brightness level (0 is min, 15 is max) 
    lc.clearDisplay(0); // To Clear the display register 
     ts.add(2, 2000, [&](void*){
        printTwoNumb(t, 4);
        printSymbolTermo();
     }, nullptr, true);
}

void printTwoNumb(float value_t, int position){
    int value = value_t*10;
    int numInPos1, numInPos2, numInPos3; 
     numInPos1 = value%10;
     numInPos2 = ((value%100)-numInPos1)/10;
     numInPos3 = ((value%1000)-numInPos2)/100;
    lc.setDigit(0,position,numInPos1, false);
    lc.setDigit(0,position+1,numInPos2, true);
    lc.setDigit(0,position+2,numInPos3, false);
}

void printSymbolTermo(){
 lc.setRow(0,2,B01001110); // "С"
 lc.setRow(0,3,B01100011); // символ градус
} 
