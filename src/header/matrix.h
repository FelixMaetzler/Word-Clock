#include "FastLED.h"
#include <vector>
#include "release.h"
#include "numbers5x3.h"
#include "font7x5.h"

class Matrix
{
private:
    std::vector<std::vector<CRGB>> matrix;

public:
    // Constructors

    Matrix();

    // Methodds

    CRGB get_LED(const uint8_t, const uint8_t) const;
    void set_LED(const CRGB, const uint8_t, const uint8_t);
    void matrix_to_LEDArray(CRGB *) const;
    void shift_Left();
    constexpr void set_last_col(const std::array<CRGB, rowcount>);
    void set_digital_clock(const tm, const CRGB);
    void clear();
    uint16_t scrolling_text(const uint16_t, String &, const CRGB);
    void set_letter(const std::array<std::array<bool, 5>, 7>, const uint8_t, const uint8_t, const CRGB);
};

inline CRGB bool_to_color(const bool, const CRGB);