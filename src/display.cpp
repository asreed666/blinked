#include "mbed.h"
#include "constants.h"
#include "display.h"

extern things_t myData;

void displayTask() {
    DigitalOut green(GREENLED);

    while(true) {
        ThisThread::sleep_for(500ms);
        printf("The button is %s\n", myData.buttonState?"pressed":"not pressed");
        if (myData.buttonState == true) green = true;
        else green = false;
    }

}