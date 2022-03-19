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
void Matrix::replace_last_col(std::array<CRGB, rowcount> col)
{
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
    constexpr uint8_t const_row_begin = 0;
    constexpr uint8_t const_col_begin = 2;
    uint8_t row_begin;
    uint8_t col_begin;

    for (uint8_t i = 0; i < 4; i++)
    {
        auto number = decompress5x3(Numbers5x3[array[i]]);
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
                bool_to_color(OnOff, color);
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
uint16_t Matrix::scrolling_text(const uint16_t framecounter, String &sentence, const CRGB color)
{
    const uint8_t letterIndex = framecounter / 6;
    const uint8_t letterColIndex = framecounter % 6;
    const char letter = sentence.charAt(letterIndex);
    std::array<CRGB, rowcount> matrix_last_col;
    matrix_last_col.fill(CRGB::Black);
    constexpr uint8_t start = (rowcount / 2) - 3;
    std::array<std::array<bool, 5>, 7> letterbuffer;
    if (letterColIndex == 5)
    {
        // you need an emty col
    }
    else if (letter >= 'A' && letter <= 'Z')
    {
        letterbuffer = decompress7x5(CapitalLetters7x5[letter - 'A']);
    }
    else if (letter >= '0' && letter <= '9')
    {
        letterbuffer = decompress7x5(Numbers7x5[letter - '0']);
    }
    else if (letter == ' ')
    {
        // its the space bar
    }
    else
    {
        DEBUG_PRINT("scrolling_text() has gotten an undefined character");
    }

    for (uint8_t i = start; i < start + 7; i++)
    {
        matrix_last_col[i] = bool_to_color(letterbuffer[i][4], color);
    }
    this->shift_Left();
    this->replace_last_col(matrix_last_col);
}
void Matrix::set_letter(const std::array<std::array<bool, 5>, 7> letter, const uint8_t rowStart, const uint8_t colStart, const CRGB color)
{
    DEBUG(if (rowStart + 5 >= rowcount || rowStart < 0 || colStart < 0 || colStart + 7 >= colcount) {
        DEBUG_PRINT("set_letter has not allowed indizies (Over oer Underflow");
    });
    for (uint8_t row = rowStart; row < rowStart + 7; row++)
    {
        for (uint8_t col = colStart; col < colStart + 5; col++)
        {
            this->set_LED(bool_to_color(letter.at(row).at(col), color), row, col);
        }
    }
}
CRGB bool_to_color(const bool x, const CRGB color)
{
    if (x)
    {
        return color;
    }
    else
    {
        return CRGB::Black;
    }
}