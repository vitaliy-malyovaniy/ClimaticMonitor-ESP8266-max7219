#include <Arduino.h>
#include "max7219displayTest.h"

extern LedControl lc;
unsigned long delaytime=250;
unsigned long delaytime1=150;

void displayDemo(){
  Serial.println("Starting display Demo");  
    // test afisare un anumit text
lc.clearDisplay(0); // To Clear the display register 
 
lc.setDigit(0,7,2, false); // To display the 2 first column on the left (column 7) 
lc.setDigit(0,6,5, true); // To display a 5 column 6 and decimal point
lc.setDigit(0,5,4, false); // To display a 4 column 5
lc.setRow(0,4,B1001110);
lc.setDigit(0,2,3, false); // To show the 5 on 2nd 
lc.setDigit(0,1,7, false); // To Place a 0 in the column 1
lc.setRow(0,0,B0110111);
 
delay(1000);
 
// fac alt text
lc.clearDisplay(0); // Clear display register 
lc.setDigit(0,7,1, false); // To display a 1 at the first column on the left (column 7) 
lc.setDigit(0,6,2, false); // To display a 2 column 6 and decimal point
lc.setRow(0,5,B00000001);
lc.setDigit(0,4,4, false); // display a "4" in column 4
lc.setDigit(0,3,2, false); // display a "2" in column 3
lc.setRow(0,2,B00000001);
lc.setDigit(0,1,3, false); // To display a 3 column 1
lc.setDigit(0,0,6, false); // 6 show a first hand column, column 0
 
delay(1000);
 
// fac inca un text
lc.clearDisplay(0); // To Clear the display register 
lc.setRow(0,6,B01100010); // "n" 
lc.setRow(0,5,B00100000); // "i" 
lc.setRow(0,4,B01110011); // "q" 
lc.setRow(0,3,B00000001);  
lc.setRow(0,2,B01000010); // "r" 
lc.setRow(0,1,B01100011); // "o"  
 
delay(1000); // Delay 3 Seconds
lc.clearDisplay(0);
}

void writeArduinoOn7Segment() {
    Serial.println("write Arduino On 7 Segment");
  lc.setChar(0,0,'a',false);
  delay(delaytime);
  lc.setRow(0,0,0x05);
  delay(delaytime);
  lc.setChar(0,0,'d',false);
  delay(delaytime);
  lc.setRow(0,0,0x1c);
  delay(delaytime);
  lc.setRow(0,0,B00010000);
  delay(delaytime);
  lc.setRow(0,0,0x15);
  delay(delaytime);
  lc.setRow(0,0,0x1D);
  delay(delaytime);
  lc.clearDisplay(0);
  delay(delaytime);
} 

/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
void scrollDigits() {
    Serial.println("Scrol Digit");
  for(int i=0;i<13;i++) {
    lc.setDigit(0,0,i+4,false);  
        delay(delaytime1);
    lc.setDigit(0,1,i+3,false);    
        delay(delaytime1);
    lc.setDigit(0,2,i+2,false);
        delay(delaytime1);    
    lc.setDigit(0,3,i+1,false);
        delay(delaytime1);    
    lc.setDigit(0,4,i,false);
        delay(delaytime1);    
  }
  lc.clearDisplay(0);
  delay(delaytime);
}
 