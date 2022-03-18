#include "FastLED.h"
#include <vector>
#include "release.h"
#include "numbers5x3.h"

class Matrix
{
private:
    std::vector<std::vector<CRGB>> matrix;

public:
    // Constructors

    Matrix();

    // Methodds

    CRGB get_LED(uint8_t, uint8_t) const;
    void set_LED(CRGB, uint8_t, uint8_t);
    void matrix_to_LEDArray(CRGB *) const;
    void shift_Left();
    void replace_last_col(std::vector<CRGB>);
    void set_digital_clock(const tm, CRGB);
    void clear();
};
