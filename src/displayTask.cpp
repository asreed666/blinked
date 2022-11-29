#include "mbed.h"
#include "constants.h"
#include "displayTask.h"

extern things_t myData;

void displayTask() {
/* setup */
    DigitalOut green(greenLed);
    while(true){ /* loop forever */
        ThisThread::sleep_for(100ms);
        green = myData.switchState;
    }

}