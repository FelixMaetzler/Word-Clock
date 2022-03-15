#include "FastLED.h"
#include "release.h"

constexpr int num_leds = rowcount * colcount;
constexpr int led_pin = 6;

extern CRGB leds[num_leds];

void led_setup();
