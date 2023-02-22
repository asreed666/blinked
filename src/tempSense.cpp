#include "tempSense.h"
#include "constants.h"
#include "mbed.h"

extern things_t myData;
// DigitalOut vdd(thermPower);
// DigitalOut gnd(thermGround);
AnalogIn temperatureVoltage(thermOut);

void readTemp() {
  // Power on the thermistor
  //    gnd = false;
  //    vdd = true;
  // read the voltage from thermistor
  while (true) {
    float refVoltage =
        temperatureVoltage.read() * 2.4; // Range of ADC 0->2*Vref
    // power off the thermistor
    //    vdd = false;
    float refCurrent = refVoltage / 10000.0; // 10k Reference Resistor
    float thermVoltage = 3.3 - refVoltage;   // Assume supply voltage is 3.3v
    float thermResistance = thermVoltage / refCurrent;
    float logrT = (float32_t)log((float64_t)thermResistance);
    /* Calculate temperature from the resistance of thermistor using
     * Steinhart-Hart Equation */
    float stEqn = (float32_t)((A_COEFF) + ((B_COEFF)*logrT) +
                              ((C_COEFF)*pow((float64)logrT, (float32)3)));
    float temperatureC = (float32_t)(((1.0 / stEqn) + ABSOLUTE_ZERO) + 0.05);
    myData.temperature = temperatureC;
        if (myData.temperature > myData.setTemp + 2.0f) {
        myData.heaterState = false;
    }
    if (myData.temperature < myData.setTemp - 2.0f) {
        myData.heaterState = true;
    }
    ThisThread::sleep_for(1000);
  }
}