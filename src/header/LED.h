#include "NeoPixelBus.h"
#include "NeoPixelAnimator.h"

#include "release.h"
#include "stdlib.h"

constexpr uint16_t num_leds = rowcount * colcount;
constexpr uint8_t led_pin = 6;



void led_setup();
