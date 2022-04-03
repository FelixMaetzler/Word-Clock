#include <FS.h>
#include "LittleFS.h"
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "release.h"

#include "LED.h"

extern uint8_t led_count;
extern String ledState;
extern String Scrolling_Text;
extern Strip strip;

extern bool modeWordClock;
extern bool modeDigitalClock;
extern bool modeScrollingText;
String processor(const String &);
void webserver_Setup();