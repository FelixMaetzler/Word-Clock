

#include "FastLED.h"
#include "release.h"
#include "stdlib.h"

constexpr uint16_t num_leds = rowcount * colcount;
constexpr uint8_t led_pin = 6;

extern CRGB leds[num_leds];

void led_setup();
