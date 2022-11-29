#include "mbed.h"
#include "constants.h"
#include "lightLevel.h"

extern things_t myData;

AnalogIn lightLevelV( lightOut );

void readLight() {
    myData.lightLevel = lightLevelV.read() * 100; // Range of light level 0 to 100%
        ThisThread::sleep_for(1s);
}