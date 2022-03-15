#include "FastLED.h"
#include <vector>
#include "release.h"

class Matrix
{
private:
    std::vector<std::vector<CRGB>> matrix;

public:
    // Konstruktoren

    Matrix();

    // Methoden

    CRGB get_LED(int, int) const;
    void set_LED(CRGB, int, int);
    void matrix_to_LEDArray(CRGB *) const;
    void nachLinksSchieben();
    void letzteSpalteErsetzen(std::vector<CRGB>);
};
