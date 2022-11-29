#include "mbed.h"
#include "constants.h"
#include "switchPos.h"

DigitalIn switchValue( switchPort );
int switchPos() {
    return switchValue;
}