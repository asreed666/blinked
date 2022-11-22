#include "mbed.h"
#include "constants.h"
#include "lightLevel.h"

AnalogIn lightLevelV( lightOut );

float readLight() {
    float lightLevel = lightLevelV.read() * 100; // Range of light level 0 to 100%

    return lightLevel;
}