#include "FastLED.h"
#include "release.h"

#define NUM_LEDS ROWCOUNT *COLCOUNT
#define DATA_PIN 6

extern CRGB leds[NUM_LEDS];

void led_setup();
