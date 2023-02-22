#ifndef CONSTANTS
#define CONSTANTS
// Blinking rate in milliseconds
#define BLINKING_RATE     2000
#define thermPower P10_3
#define thermGround P10_0
#define thermOut P10_1
#define GREENLED P0_5
#define PUSH_BUTTON P10_3 // P0_4 doesn't work when wifi is running
#define lightOut P10_4

/* Reference resistor in series with the thermistor is of 10kohm */
#define R_REFERENCE                         (float)(10000)

/* A constant of NCP18XH103F03RB thermistor is */
#define A_COEFF                          (float)(0.0009032679f)
/* B constant of NCP18XH103F03RB thermistor is */
#define B_COEFF                          (float)(0.000248772f)
/* C constant of NCP18XH103F03RB thermistor is */
#define C_COEFF                          (float)(0.0000002041094f)

/* Zero Kelvin in degree C */
#define ABSOLUTE_ZERO                    (float)(-273.15)
struct things_t {
    float tempC;
    float setTemp = 18.0f;
    bool heaterState;
    float lightL;
    float setLightLevel = 50.0f;
    bool lightState;
    bool buttonState;
};

#endif