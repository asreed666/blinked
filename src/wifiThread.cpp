#include "mbed.h"

WiFiInterface *wifi;

const char *sec2str(nsapi_security_t sec)
{
    switch (sec) {
        case NSAPI_SECURITY_NONE:
            return "None";
        case NSAPI_SECURITY_WEP:
            return "WEP";
        case NSAPI_SECURITY_WPA:
            return "WPA";
        case NSAPI_SECURITY_WPA2:
            return "WPA2";
        case NSAPI_SECURITY_WPA_WPA2:
            return "WPA/WPA2";
        case NSAPI_SECURITY_UNKNOWN:
        default:
            return "Unknown";
    }
}
int wifiThreadTask()
{
    // Connect to wifi
    wifi = WiFiInterface::get_default_instance();
    if (!wifi) {
        printf("ERROR: No WiFiInterface found.\n");
        return -1;
    } else {
        printf("Connected to wifi");
    }

    while(true) {
        ThisThread::sleep_for(100ms);
    }
}