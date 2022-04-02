#include "NeoPixelBus.h"
#include "NeoPixelAnimator.h"
#include "helperfunctions.h"
#include "RGB.h"
#include "HSL.h"
#include "release.h"
#include "stdlib.h"
#pragma once
constexpr uint16_t num_leds = rowcount * colcount + 4;
constexpr uint8_t led_pin = 6;

class Strip
{
private:
    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip;

public:
Strip() : strip(num_leds){};
    void show();
    void begin();
    void set_led(uint16_t, RGB);
    void rainbow(uint16_t, uint16_t, uint8_t);
    void clear();
};

void led_setup();

