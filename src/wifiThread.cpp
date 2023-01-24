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
        printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
        int ret = wifi->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
        if (ret != 0) {
            printf("\nConnection error: %d\n", ret);
        return -1;
    }

        /* print the network info */
        SocketAddress a;
        wifi->get_ip_address(&a);
        printf("IP address: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");
        wifi->get_netmask(&a);
        printf("Netmask: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");
        wifi->get_gateway(&a);
        printf("Gateway: %s\r\n", a.get_ip_address() ? a.get_ip_address() : "None");


    }

    while(true) {
        ThisThread::sleep_for(100ms);
    }
}