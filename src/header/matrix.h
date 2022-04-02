#include "numbers5x3.h"
#include "LED.h"
#include <vector>
#include "release.h"

#include "font7x5.h"
#include "words_german.h"
#include "ntp.h"

#pragma once
class Matrix
{
private:
    std::vector<std::vector<RGB>> matrix;

public:
    // Constructors

    Matrix();

    // Methods

    RGB get_LED(const uint8_t, const uint8_t) const;
    void set_LED(const RGB, const uint8_t, const uint8_t);
    void matrix_to_LEDArray(Strip *) const;
    void shift_Left();
    void set_last_col(const std::array<RGB, rowcount>);
    void set_digital_clock(const tm, const std::array<RGB, 4> color = {RGB(10,0,0), RGB(0,10,0), RGB(0,0,10), RGB(10,0,10)});
    void clear();
    uint16_t scrolling_text(const uint16_t, String &, const RGB);
    void set_letter(const std::array<std::array<bool, 5>, 7>, const uint8_t, const uint8_t, const RGB);
    void set_word(const word, const RGB color);
    void set_time_in_words_german(const time_t, const RGB);
    String to_string() const;
    void debug_print() const;
};

inline RGB bool_to_color(const bool, const RGB);
