#include "mbed.h"
#include "constants.h"
#include "switchPos.h"

extern things_t myData;
DigitalIn switchValue( switchPort );
void switchPos() {

    /* set stuff up */

    while(true){ /* loop forever */
        ThisThread::sleep_for(50ms);
        myData.switchState = !switchValue; /* check the switch input */
    }

}