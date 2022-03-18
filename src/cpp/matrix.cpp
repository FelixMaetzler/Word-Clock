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
void Matrix::set_digital_clock(const tm time, CRGB color)
{
    const uint8_t hour_tens_digit = time.tm_hour / 10;
    const uint8_t hour_ones_digit = time.tm_hour % 10;
    const uint8_t min_tens_digit = time.tm_min / 10;
    const uint8_t min_ones_digit = time.tm_min % 10;
    const uint8_t array[] = {hour_tens_digit, hour_ones_digit, min_tens_digit, min_ones_digit};
    const uint8_t const_row_begin = 0;
    const uint8_t const_col_begin = 2;
    uint8_t row_begin;
    uint8_t col_begin;

    for (uint8_t i = 0; i < 4; i++)
    {
        auto number = InttoArray5x3(Numberarray5x3[array[i]]);
        switch (i)
        {
        case 0:
            row_begin = const_row_begin + 0;
            col_begin = const_col_begin + 1;
            break;
        case 1:
            row_begin = const_row_begin + 0;
            col_begin = const_col_begin + 7;
            break;
        case 2:
            row_begin = const_row_begin + 5;
            col_begin = const_col_begin + 1;
            break;
        case 3:
            row_begin = const_row_begin + 5;
            col_begin = const_col_begin + 7;
            break;
        }

        for (uint8_t row = row_begin; row < row_begin + 5; row++)
        {
            for (uint8_t col = col_begin; col < col_begin + 3; col++)
            {
                bool OnOff = number[row - row_begin][col - col_begin];
                if (OnOff)
                {
                    this->set_LED(color, row, col);
                }
                else
                {
                    this->set_LED(CRGB::Black, row, col);
                }
            }
        }
    }
}
void Matrix::clear()
{
    for (uint8_t row = 0; row < rowcount; row++)
    {
        for (uint8_t col = 0; col < colcount; col++)
        {
            this->set_LED(CRGB::Black, row, col);
        }
    }
}