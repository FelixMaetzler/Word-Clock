#include "header/matrix.h"

/*
Standartconstructor
*/
Matrix::Matrix() : matrix(rowcount, std::vector<CRGB>(colcount)) {}

CRGB Matrix::get_LED(uint8_t row, uint8_t col) const
{
    DEBUG(
        if (row >= rowcount || row < 0 || col >= colcount || col < 0) {
            DEBUG_PRINT("get_LED was called with wrong Parameters (Over or Unterflow");
            return CRGB();
        });
    return matrix.at(row).at(col);
}
void Matrix::set_LED(CRGB led, uint8_t row, uint8_t col)
{
    DEBUG(
        if (row >= rowcount || row < 0 || col >= colcount || col < 0) {
            DEBUG_PRINT("set_LED was called with wrong Parameters (Over or Unterflow");
        });
    this->matrix[row][col] = led;
}
void Matrix::matrix_to_LEDArray(CRGB *leds) const
{
#if SERPENTINES
    uint16_t i;
    for (uint8_t row = 0; row < rowcount; row++)
    {
        if (row % 2 == 0)
        {
            // from left to right
            for (uint8_t col = 0; col < colcount; col++)
            {
                i = row * colcount + col;
                leds[i] = this->get_LED(row, col);
            }
        }
        else
        {
            // from right to left
            uint8_t counter = 0;
            for (uint8_t col = colcount - 1; col >= 0; col--)
            {
                i = row * colcount + counter;
                leds[i] = this->get_LED(row, col);
                counter++;
            }
        }
    }
#endif

#if LINEBYLINE
    uint16_t i;
    for (uint8_t row = 0; row < rowcount; row++)
    {
        for (uint8_t col = 0; col < colcount; col++)
        {
            i = row * colcount + col;
            leds[i] = this->get_LED(row, col);
        }
    }
#endif
}
void Matrix::shift_Left()
{
    for (auto &row : this->matrix)
    {
        auto x = row.begin();
        std::rotate(x, x + 1, x + colcount);
    }
}
void Matrix::replace_last_col(std::vector<CRGB> col)
{
    DEBUG(if (col.size() != rowcount) {
        DEBUG_PRINT("replace_last_col dont work. Vector doesent fit");
        return;
    });
    for (uint8_t row = 0; row < rowcount; row++)
    {
        this->set_LED(col.at(row), row, colcount - 1);
    }
}