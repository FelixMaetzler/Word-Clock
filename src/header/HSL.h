#include "NeoPixelBus.h"

#pragma once

class RGB;
class HSL
{
    uint8_t h; // Hue
    uint8_t s; // Saturation
    uint8_t l; // Lightnss

public:
    HSL(uint8_t, uint8_t, uint8_t);
    uint8_t get_h() const;
    uint8_t get_s() const;
    uint8_t get_l() const;
    void set_h(const uint8_t);
    void set_s(const uint8_t);
    void set_l(const uint8_t);
    HSL(const RGB);
    HslColor convert() const;
};