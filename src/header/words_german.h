#include "release.h"
#include "Arduino.h"
#include <cstdlib>
#include <array>
#pragma once

enum wording
{
    es,
    ist,
    fuenfX,
    zehnX,
    nach,
    bis,
    dreiX,
    halb,
    viertel,
    eins,
    sechs,
    zwei,
    zehn,
    neun,
    drei,
    fuenf,
    zwoelf,
    sieben,
    vier,
    acht,
    elf
};
struct encode
{
    uint8_t row_begin;
    uint8_t col_begin;
    uint8_t length;
    bool direction; // true left and false down
    /*
    Constructor
    direction: true = left and false = down
    */
    constexpr encode(uint8_t row_begin, uint8_t col_begin, uint8_t length, bool direction)
        : row_begin(row_begin),
          col_begin(col_begin),
          length(length),
          direction(direction){};
};

wording int_to_word(const uint8_t);