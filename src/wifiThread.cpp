#include "wifiThread.h"
#include "MQTTClientMbedOs.h"
#include "constants.h"
#include "config.h"
#include "mbed.h"

WiFiInterface *wifi;
constexpr int NUM_TOPICS = 20;
constexpr int TOPIC_LEN = 80;
constexpr auto LIGHT_LEVELTOPIC = 0;
constexpr auto LIGHT_STATE_TOPIC = 1;
constexpr auto LIGHT_SWITCH_TOPIC = 2;
constexpr auto REDLED_TOPIC = 3;
constexpr auto GREENLED_TOPIC = 4;
constexpr auto BLUELED_TOPIC = 5;
constexpr auto ANNOUNCETOPIC = 6;
constexpr auto LIGHT_THRESH_TOPIC = 7;
constexpr auto LATITUDE_TOPIC = 8;
constexpr auto LONGITUDE_TOPIC = 9;
constexpr auto TEMPERATURETOPIC = 10;
constexpr auto TEMP_THRESH_TOPIC = 11;
constexpr auto RX_COUNT = 12;
constexpr auto TX_COUNT = 13;
constexpr auto TIME = 14;
constexpr auto STATUSLED_TOPIC = 15;
constexpr auto ORANGELED_TOPIC = 16;
constexpr auto HEATER_STATE_TOPIC = 17;
constexpr auto HEATER_SWITCH_TOPIC = 18;
constexpr auto REL_HUMIDITY_TOPIC = 19;

const char *sec2str(nsapi_security_t sec) {
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
void wifiThreadTask() {
  char buffer[80];
  char topicBuffer[80];
  uint32_t rc;
  const char topicMap[NUM_TOPICS][TOPIC_LEN] = {
      "light",   "lightState", "lightSwitch", "redled", "greenled",
      "blueled", "announce",   "lthresh",     "latitude",  "longitude",
      "temperature", "tempthresh", "rxCount", "txCount", "time", "statusled",
      "orangeled", "heaterState", "heaterSwitch", "humidity"};

  
  // Connect to wifi
  wifi = WiFiInterface::get_default_instance();
  if (!wifi) {
    printf("ERROR: No WiFiInterface found.\n");
    // return -1;
  } else {
    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    int ret =
        wifi->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD,
                      NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
      printf("\nConnection error: %d\n", ret);
      // return -1;
    }

    /* print the network info */
    SocketAddress a;
    wifi->get_ip_address(&a);
    printf("\033[3;1HIP address: %s\r\n",
           a.get_ip_address() ? a.get_ip_address() : "None");
    //    wifi->get_netmask(&a);
    //    printf("Netmask: %s\r\n", a.get_ip_address() ? a.get_ip_address() :
    //    "None"); wifi->get_gateway(&a); printf("Gateway: %s\r\n",
    //    a.get_ip_address() ? a.get_ip_address() : "None");
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.clientID.cstring = (char *)THING_NAME;
    data.keepAliveInterval = 20;
    data.cleansession = 1;
    data.username.cstring = (char *)"";
    data.password.cstring = (char *)"";
    char *host = (char *)MQTT_BROKER;
    uint16_t port = 1883;
    TCPSocket socket;
    MQTTClient client(&socket);
    socket.open(wifi);
    rc = socket.connect(host, port);
    if (rc == 0) {
      printf("Succesful connection of socket to Host %s port %d\n", host, port);
    } else {
      printf("Socket connection failed");
      while (socket.connect(host, port)) {
        printf(".");
      }
    }
    rc = client.connect(data);
    if (rc == 0) {
      printf("Succesful connection of %s to Broker\n", data.clientID.cstring);
    } else {
      printf("Client connection failed");
    }
    MQTT::Message message{};
    sprintf(buffer, "Hello chaps! from %s\r\n", THING_NAME);
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void *)buffer;
    message.payloadlen = strlen(buffer) + 1;

    rc = client.publish(topicMap[ANNOUNCETOPIC], message);
    if (rc == 0)
      printf("publish announce worked\n");
    else {
      printf("publish announce failed %d\n", rc);
    }
  }

  while (true) {
    ThisThread::sleep_for(100);
  }
}