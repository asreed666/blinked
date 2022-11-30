#include "mbed.h"
#include "constants.h"
#include "button.h"

DigitalIn userButton(PUSH_BUTTON);
bool readButtonState() {
    return !(bool)userButton;
}
