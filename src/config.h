#ifndef CONFIG
#define CONFIG
/* MQTT configuration file
 *
 * Set your unique THING_NAME
*/

#define BROKER          "192.168.1.176"
#define PORT            1883

#define THING_NAME      "asrThingy"

//#define TEMPERATURE_TOPIC   "/temperatureC"
//#define LIGHT_LEVEL_TOPIC   "/lightlevel"
#define ANNOUNCE_TOPIC      "/announce"
#define LIGHT_SET_TOPIC "asrThingy/lthresh"

#endif