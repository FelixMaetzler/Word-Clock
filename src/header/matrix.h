#include "numbers5x3.h"
#include "NeoPixelBus.h"
#include "NeoPixelAnimator.h"
#include <vector>
#include "release.h"

#include "font7x5.h"
#include "words_german.h"
#include "ntp.h"

#pragma once
class Matrix
{
private:
    std::vector<std::vector<RgbColor>> matrix;

public:
    // Constructors

    Matrix();

    // Methods

    RgbColor get_LED(const uint8_t, const uint8_t) const;
    void set_LED(const RgbColor, const uint8_t, const uint8_t);
    void matrix_to_LEDArray(NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *) const;
    void shift_Left();
    void set_last_col(const std::array<RgbColor, rowcount>);
    void set_digital_clock(const tm, const RgbColor);
    void clear();
    uint16_t scrolling_text(const uint16_t, String &, const RgbColor);
    void set_letter(const std::array<std::array<bool, 5>, 7>, const uint8_t, const uint8_t, const RgbColor);
    void set_word(const word, const RgbColor color);
    void set_time_in_words_german(const time_t, const RgbColor);
    String to_string() const;
    void debug_print() const;
};

inline RgbColor bool_to_color(const bool, const RgbColor);
