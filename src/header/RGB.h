#include "NeoPixelBus.h"
#include <cmath>
#pragma once

class HSL;
class RGB
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

public:
    RGB();
    RGB(uint8_t, uint8_t, uint8_t);
    uint8_t get_r() const;
    uint8_t get_g() const;
    uint8_t get_b() const;
    void set_r(const uint8_t);
    void set_g(const uint8_t);
    void set_b(const uint8_t);
    RGB(const HSL);
    RGB(uint8_t);
    uint8_t max() const;
    RgbColor convert() const;
};