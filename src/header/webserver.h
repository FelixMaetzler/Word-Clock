#include <FS.h>
#include "LittleFS.h"
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "LED.h"

extern uint8_t led_count;
extern String ledState;
extern Strip strip;
String processor(const String &);
void webserver_Setup();