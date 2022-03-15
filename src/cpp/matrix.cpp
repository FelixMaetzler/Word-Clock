#include "header/matrix.h"

/*
Standartkonstruktor
*/
Matrix::Matrix() : matrix(ZEILENZAHL, std::vector<CRGB>(SPALTENZAHL)) {}

CRGB Matrix::get_LED(int zeile, int spalte) const
{
    DEBUG(
        if (zeile >= ZEILENZAHL || zeile < 0 || spalte >= SPALTENZAHL || spalte < 0) {
            DEBUG_PRINT("get_LED wurde mit falschen Parametern aufgerufen (Over oder Unterflow");
            return int();
        });
    return matrix.at(zeile).at(spalte);
}
void Matrix::set_LED(CRGB led, int zeile, int spalte)
{
    DEBUG(
        if (zeile >= ZEILENZAHL || zeile < 0 || spalte >= SPALTENZAHL || spalte < 0) {
            DEBUG_PRINT("set_LED wurde mit falschen Parametern aufgerufen (Over oder Unterflow");
        });
    this->matrix[zeile][spalte] = led;
}
void Matrix::matrix_to_LEDArray(CRGB *leds) const
{
#if SERPENTINEN
    int i;
    for (int zeile = 0; zeile < ZEILENZAHL; zeile++)
    {
        if (zeile % 2 == 0)
        {
            // von links nach rechts
            for (int spalte = 0; spalte < SPALTENZAHL; spalte++)
            {
                i = zeile * SPALTENZAHL + spalte;
                leds[i] = this->get_LED(zeile, spalte);
            }
        }
        else
        {
            // von rechts nach links
            int counter = 0;
            for (int spalte = SPALTENZAHL - 1; spalte >= 0; spalte--)
            {
                i = zeile * SPALTENZAHL + counter;
                leds[i] = this->get_LED(zeile, spalte);
                counter++;
            }
        }
    }
#endif

#if ZEILENWEISE
    int i;
    for (int zeile = 0; zeile < ZEILENZAHL; zeile++)
    {
        for (int spalte = 0; spalte < SPALTENZAHL; spalte++)
        {
            i = zeile * SPALTENZAHL + spalte;
            leds[i] = this->get_LED(zeile, spalte);
        }
    }
#endif
}
void Matrix::nachLinksSchieben()
{
    for (auto &zeile : this->matrix)
    {
        auto x = zeile.begin();
        std::rotate(x, x + 1, x + SPALTENZAHL);
    }
}
void Matrix::letzteSpalteErsetzen(std::vector<CRGB> spalte)
{
    DEBUG(if (spalte.size() != ZEILENZAHL)
    {
        DEBUG_PRINT("letzteSpalteErsetzen geht nicht. Vektor passt nicht");
        return;
    }
    );
    for (int zeile = 0; zeile < ZEILENZAHL; zeile++)
    {
        this->set_LED(spalte.at(zeile), zeile, SPALTENZAHL - 1);
    }
}