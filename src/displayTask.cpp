#include "displayTask.h"
#include "constants.h"
#include "mbed.h"
#include "stdio.h"
#include "vt100.h"

extern things_t myData;
void displayTask() {
  /* setup */
  int period = 0;
  DigitalOut green(greenLed);
  printf("\033[2J"); // Clear the VT100 terminal display
  ThisThread::sleep_for(1s);
  printf("\033[?25l");
  while (true) { /* loop forever */
    ThisThread::sleep_for(100ms);
    green = myData.switchState;
    if (period++ > 4) {
      printf("\033[H"); // put cursor in position 1,1
      printf("\033[1m");
      printf("\033[1;20HEnvironmental Monitor");
//      printf("\033[m");
      printf("\033[8;3HLed is %s\n", myData.switchState
                                         ? "\033[0;31mOn \033[0;37m"
                                         : "\033[0;32mOff\033[0;37m");
      printf("\033[8;1H%s", myData.switchState
                                         ? "\033[1;42m \033[0;40m" 
                                         : " ");
      printf("\033[10;3HTemperature is: %2.1fC\n", myData.temperature);
      printf("\033[10;1H%s", myData.heaterState
                                         ? "\033[1;41m \033[0;40m" 
                                         : "\033[1;42m \033[0;40m");
      printf("\033[12;1H%s", myData.lightState
                                         ? "\033[1;41m \033[0;40m" 
                                         : "\033[1;42m \033[0;40m");
      printf("\033[12;3HLight is at %3.0f%c\n", myData.lightLevel, '%');
      period = 0;
    }
  }
}