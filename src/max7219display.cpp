#include "max7219display.h"

LedControl lc(13,14,12,1);

void max7219displayInit(void){
    // Initialize the MAX7219 
Serial.println("Initialize the MAX7219...");
lc.shutdown(0,false); // To Enable the Display 
lc.setIntensity(0,15); // To set the brightness level (0 is min, 15 is max) 
lc.clearDisplay(0); // To Clear the display register 
}

void printTwoNumb(int value, int position){
    int numInPos1, numInPos2; 
     numInPos1 = value%10;
     numInPos2 = ((value%100)-numInPos1)/10;
    lc.setDigit(0,position,numInPos1, false);
    lc.setDigit(0,position+1,numInPos2, false);
}

void printSymbolTermo(){
 lc.setRow(0,3,B01001110); // "С"
 lc.setRow(0,4,B01100011); // символ градус
} 
