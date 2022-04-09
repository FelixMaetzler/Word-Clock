#include <FS.h>
#include "LittleFS.h"
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>
#include "release.h"

#include "LED.h"

extern uint8_t led_count;
extern String ledState;
extern String Scrolling_Text;
extern Strip strip;

extern bool modeWordClock;
extern bool modeDigitalClock;
extern bool modeScrollingText;

constexpr uint8_t json_elements_count = 20;
String processor(const String &);
void webserver_Setup();
void websocket_Setup();
void onEvent(AsyncWebSocket *server,
             AsyncWebSocketClient *client,
             AwsEventType type,
             void *arg,
             uint8_t *data,
             size_t len);
void onRootRequest(AsyncWebServerRequest *request);
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void notifyClients();