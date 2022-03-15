#include "header/LED.h"

void led_setup()
{
  FastLED.addLeds<WS2812B, led_pin, GRB>(leds, num_leds);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
}
