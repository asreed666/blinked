#include "mbed.h"
#include "constants.h"
#include "vt100.h"
#include "display.h"

extern things_t myData;

void displayTask() {
    DigitalOut green(GREENLED);
    printf("\033[2J");  // Clear the terminal display
    ThisThread::sleep_for(100);
    printf("\033[?25l"); // Hide the Visible Cursor

    printf("\033[1;20H\033[1;37mEnvironmental Sensing\033[0;37m");
    ThisThread::sleep_for(100);

    while (true) {
      ThisThread::sleep_for(500);
      printf("\033[8;3HThe LED is %s\n",
             myData.buttonState ? "\033[1;32mOn \033[0;37m" 
                                : "\033[2;32mOff\033[0;37m");
      if (myData.buttonState == true) {
        green = true;
      } else {
        green = false;
      }
      ThisThread::sleep_for(1);
      printf("\033[10;3HTemperature: %2.1fC \n", myData.tempC);
      printf("\033[10;1H%s", myData.heaterState
                             ? "\033[41m \033[40m"
                             : "\033[42m \033[40m" );
      printf("\033[12;3HLight Level: %3.0f%c \033[J", myData.lightL, '%');
      printf("\033[12;1H%s", myData.lightState
                             ? "\033[41m \033[40m"
                             : "\033[42m \033[40m" );
      ThisThread::sleep_for(500);
    }

}