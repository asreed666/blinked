#include "mbed.h"
#include "constants.h"
#include "vt100.h"
#include "display.h"

extern things_t myData;

void displayTask() {
    DigitalOut green(GREENLED);
    RIS;  // reset vt100 terminal
    while(true) {
        ThisThread::sleep_for(500ms);
        HOME; // VT100 Home the cursor
        CYAN_TEXT;
        printf("The LED is %s\n", myData.buttonState?"\033[1;32mOn ":"\033[2;32mOff");
        if (myData.buttonState == true) {
            BLUE_BOLD;
            green = true;
        }
        else {
            green = false;
            BLUE_TEXT;
        }
 
        printf("Temperature: %2.1fC \n", myData.tempC);
        GREEN_TEXT;
        printf("Light Level: %3.0f%c \n", myData.lightL, '%');
    }

}