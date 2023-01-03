#include "mbed.h"
#include "stdio.h"
#include "constants.h"
#include "displayTask.h"
#include "vt100.h"

extern things_t myData;
void displayTask() {
/* setup */
    int period = 0;
    DigitalOut green(greenLed);
    RIS; // Reset the VT100 terminal to text mode
    ThisThread::sleep_for(1s);
    HIDE_CURSOR;
    while(true){ /* loop forever */
        ThisThread::sleep_for(100ms);
        green = myData.switchState;
        if (period++ > 4) {
            HOME; // put cursor in position 1,1
            BOLD;
            printf ("\033[1;20HEnvironmental Monitor");
            NORMAL;
            printf("\033[8;3HLed is %s\n", myData.switchState?"\033[0;31mOn \033[0;37m":"\033[0;32mOff\033[0;37m");
            printf("\033[8;1H%s", myData.switchState?"\033[1;32m\033[7m \033[0;37m":" ");
            printf("\033[10;3HTemperature is: %2.1fC\n", myData.temperature);
            printf("\033[12;3HLight is at %3.0f%c\n", myData.lightLevel, '%');
            period = 0;
        }
    }

}