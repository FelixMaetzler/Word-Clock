#include "FastLED.h"
#include <vector>
#include "release.h"

class Matrix
{
private:
    std::vector<std::vector<CRGB>> matrix;

public:
    // Constructors

    Matrix();

    // Methodds

    CRGB get_LED(int, int) const;
    void set_LED(CRGB, int, int);
    void matrix_to_LEDArray(CRGB *) const;
    void shift_Left();
    void replace_last_col(std::vector<CRGB>);
};
