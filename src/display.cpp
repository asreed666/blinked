#include "mbed.h"
#include "constants.h"
#include "vt100.h"
#include "display.h"

extern things_t myData;

void displayTask() {
    DigitalOut green(GREENLED);
    RIS;  // reset vt100 terminal
    ThisThread::sleep_for(5000ms);
    HIDE_CURSOR;
    BOLD;
    
    printf("\033[1;20HEnvironmental Sensing");
    NORMAL;
    while(true) {
        ThisThread::sleep_for(500ms);
    //    HOME; // VT100 Home the cursor
        CYAN_TEXT;
        printf("\033[8;3HThe LED is %s\n", myData.buttonState?"\033[1;32mOn ":"\033[2;32mOff");
        if (myData.buttonState == true) {
            BLUE_BOLD;
            green = true;
        }
        else {
            green = false;
            BLUE_TEXT;
        }
 
        printf("\033[10;3HTemperature: %2.1fC \n", myData.tempC);
        GREEN_TEXT;
        printf("\033[12;3HLight Level: %3.0f%c \n", myData.lightL, '%');
    }

}