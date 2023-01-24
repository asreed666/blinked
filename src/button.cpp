#include "mbed.h"
#include "constants.h"
#include "button.h"

extern things_t myData;
DigitalIn userButton(P0_5);
void readButtonState() {
    /* set stuff up */
    bool lastSwitchState = userButton;
    bool pressed = false;
    while(true){ /* loop forever */
        ThisThread::sleep_for(50ms);
        if (userButton == false) {
            pressed = true;
        }
        else if (userButton == true && pressed == true) {
            myData.buttonState = !myData.buttonState;
            pressed = false;
        }
    }
}