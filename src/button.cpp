#include "mbed.h"
#include "constants.h"
#include "button.h"

extern things_t myData;
DigitalIn userButton(PUSH_BUTTON);
void readButtonState() {
    /* set stuff up */
    bool lastSwitchState = userButton;
    bool pressed = false;
    while(true){ /* loop forever */
        ThisThread::sleep_for(50ms);
        if (userButton == true) {
            pressed = true;
        }
        else if (userButton == false && pressed == true) {
            myData.buttonState = !myData.buttonState;
            pressed = false;
        }
    }
}
