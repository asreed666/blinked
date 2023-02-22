#include "mbed.h"
#include "constants.h"
#include "lightLevel.h"

extern things_t myData;


AnalogIn lightLevelV( lightOut );
void readLight() {
  while(true) {
    myData.lightLevel = lightLevelV.read() * 100; // Range of light level 0 to 100%
    if (myData.lightLevel > myData.setLight + 5.0f) {
        myData.lightState = false;
    }
    if (myData.lightLevel < myData.setLight - 5.0f) {
        myData.lightState = true;
    }
    ThisThread::sleep_for(100);
  }
}