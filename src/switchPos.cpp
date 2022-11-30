#include "mbed.h"
#include "constants.h"
#include "switchPos.h"

extern things_t myData;
DigitalIn switchValue( switchPort );
void switchPos() {

    /* set stuff up */
    bool lastSwitchState = switchValue;
    bool pressed = false;
    while(true){ /* loop forever */
        ThisThread::sleep_for(50ms);
        if (switchValue == true) {
            pressed = true;
        }
        if (switchValue == false && pressed == true) {
            myData.switchState = !myData.switchState;
            pressed = false;
        }
    }

}