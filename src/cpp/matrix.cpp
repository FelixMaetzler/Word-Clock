#include "header/matrix.h"

/*
Standartkonstruktor
*/
Matrix::Matrix() : matrix(ZEILENZAHL, std::vector<CRGB>(SPALTENZAHL)) {}

CRGB Matrix::get_LED(int zeile, int spalte)
{
    DEBUG(
        if (zeile >= ZEILENZAHL || zeile < 0 || spalte >= SPALTENZAHL || spalte < 0) {
            DEBUG_PRINT("get_LED wurde mit falschen Parametern aufgerufen (Over oder Unterflow");
        } else {
            return CRGB();
        });
    return matrix.at(zeile).at(spalte);
}
void Matrix::matrix_to_LEDArray(CRGB *leds)
{
#if SERPENTINEN
    int a = 0;
#endif

#if ZEILENWEISE
    int a = 0;
#endif
}