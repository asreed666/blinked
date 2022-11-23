/* This function reads the thermistor voltage and returns the temperature in Celsius
   using Steinhart Hart conversion from thermistor resistance
 */
#include "mbed.h"
#include "constants.h"
#include "lightlevel.h"

AnalogIn lightLevelVoltage( lightOut );

float readLightLevel() {

    // Read the light dependent resistor voltage
    float lightLevel = lightLevelVoltage.read() * 100; // Range of ADC.read 0->1
 
    return lightLevel;
}
