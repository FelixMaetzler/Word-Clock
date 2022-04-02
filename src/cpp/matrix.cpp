#include "header/matrix.h"

extern const std::array<uint64_t, 10> Numbers7x5;
extern const std::array<uint16_t, 10> Numbers5x3;
extern const std::array<uint64_t, 26> CapitalLetters7x5;
extern const std::array<encode, 21> Words;

/*
standart constructor
*/
Matrix::Matrix() : matrix(rowcount, std::vector<RGB>(colcount)) {}
/*
returns the RGB value of a LED at position (row, col) in the matrix
*/
RGB Matrix::get_LED(const uint8_t row, const uint8_t col) const
{
    DEBUG(
        if (row >= rowcount || row < 0 || col >= colcount || col < 0) {
            DEBUG_PRINT("get_LED was called with wrong Parameters (Over or Unterflow");
            return RGB(0);
        });
    return matrix.at(row).at(col);
}
/*
sets the RGB value of a LED with the position (row, col)
*/
void Matrix::set_LED(const RGB led, const uint8_t row, const uint8_t col)
{
    DEBUG(
        if (row >= rowcount || row < 0 || col >= colcount || col < 0) {
            DEBUG_PRINT("set_LED was called with wrong Parameters (Over or Unterflow");
        });
    this->matrix[row][col] = led;
}
/*
converts the matrix in the Neopixel Strip
make sure that you choose the correct LED Layout in the release.h
currenty available: Serpentines and Linebyline
*/
void Matrix::matrix_to_LEDArray(Strip *strip) const
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
                strip->set_led(i, this->get_LED(row, col));
            }
        }
        else
        {
            // from right to left
            uint8_t counter = 0;
            for (int8_t col = colcount - 1; col >= 0; col--)
            {
                i = row * colcount + counter;
                strip->set_led(i, this->get_LED(row, col));
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
            strip->set_led(i, this->get_LED(row, col));
        }
    }
#endif
}
/*
shift the entire matrix one to the left
the first column gets wrapped arrount and becomes the last column
*/
void Matrix::shift_Left()
{
    for (auto &row : this->matrix)
    {
        auto x = row.begin();
        std::rotate(x, x + 1, x + colcount);
    }
}
/*
with this method you can set the last column
you need this if you shift_left() and dont want to wrap arround
*/
void Matrix::set_last_col(const std::array<RGB, rowcount> col)
{
    for (uint8_t row = 0; row < rowcount; row++)
    {
        this->set_LED(col.at(row), row, colcount - 1);
    }
}
/*
sets the matrix to the provided tm with the provided color
*/
void Matrix::set_digital_clock(const tm time, const std::array<RGB, 4> color)
{
    const uint8_t hour_tens_digit = time.tm_hour / 10;
    const uint8_t hour_ones_digit = time.tm_hour % 10;
    const uint8_t min_tens_digit = time.tm_min / 10;
    const uint8_t min_ones_digit = time.tm_min % 10;
    const std::array<uint8_t, 4> array{{hour_tens_digit, hour_ones_digit, min_tens_digit, min_ones_digit}};
    constexpr uint8_t const_row_begin = 0;
    constexpr uint8_t const_col_begin = 0;
    uint8_t row_begin;
    uint8_t col_begin;

    for (uint8_t i = 0; i < 4; i++)
    {
        auto number = decompress5x3(array[i]);
        switch (i)
        {
        case 0:
            row_begin = const_row_begin + 0;
            col_begin = const_col_begin + 2;
            break;
        case 1:
            row_begin = const_row_begin + 0;
            col_begin = const_col_begin + 5;
            break;
        case 2:
            row_begin = const_row_begin + 5;
            col_begin = const_col_begin + 2;
            break;
        case 3:
            row_begin = const_row_begin + 5;
            col_begin = const_col_begin + 5;
            break;
        }

        for (uint8_t row = row_begin; row < row_begin + 5; row++)
        {
            for (uint8_t col = col_begin; col < col_begin + 3; col++)
            {
                bool OnOff = number[row - row_begin][col - col_begin];
                this->set_LED(bool_to_color(OnOff, color.at(i)), row, col);
            }
        }
    }
}
/*
sets every LED in the matrix to black
*/
void Matrix::clear()
{
    for (uint8_t row = 0; row < rowcount; row++)
    {
        for (uint8_t col = 0; col < colcount; col++)
        {
            this->set_LED(RGB(0), row, col);
        }
    }
}
/*
animates a scrolling text animation from right to left
you have to provide the String and the color and the frame you want to display
framecounter starts at zero and you have to count it up
so you can control the scrolling speed yourself
max framecounter is string.size() * 6
*/
uint16_t Matrix::scrolling_text(const uint16_t framecounter, String &sentence, const RGB color)
{
    const uint8_t letterIndex = framecounter / 6;
    const uint8_t letterColIndex = framecounter % 6;
    const char letter = sentence.charAt(letterIndex);
    std::array<RGB, rowcount> matrix_last_col;
    matrix_last_col.fill(RGB(0));
    constexpr uint8_t start = (rowcount / 2) - 3;
    std::array<std::array<bool, 5>, 7> letterbuffer;
    if (letterColIndex == 5)
    {
        // you need an emty col
    }
    else if ('A' <= letter && letter <= 'Z')
    {
        letterbuffer = decompress7x5(CapitalLetters7x5[letter - 'A']);
    }
    else if ('0' <= letter && letter <= '9')
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
    this->set_last_col(matrix_last_col);
    return framecounter + 1;
}
/*
this method sets one 7x5 character to the provided position in the provided color
*/
void Matrix::set_letter(const std::array<std::array<bool, 5>, 7> letter, const uint8_t rowStart, const uint8_t colStart, const RGB color)
{
    DEBUG(if (rowStart + 5 >= rowcount || rowStart < 0 || colStart < 0 || colStart + 7 >= colcount) {
        DEBUG_PRINT("set_letter has not allowed indizies (Over or Underflow");
    });
    for (uint8_t row = rowStart; row < rowStart + 7; row++)
    {
        for (uint8_t col = colStart; col < colStart + 5; col++)
        {
            this->set_LED(bool_to_color(letter.at(row).at(col), color), row, col);
        }
    }
}
/*
this is a helper function
it retuns RGB(0) if x is false and color if x is true
*/
inline RGB bool_to_color(const bool x, const RGB color)
{
    RGB result = RGB(0);
    if (x)
    {
        result = color;
    }
    return result;
}
void Matrix::set_word(const word index, const RGB color)
{
    const auto word = Words.at(index);
    if (word.direction)
    {
        // the word is in one row
        for (uint8_t col = word.col_begin; col < word.col_begin + word.length; col++)
        {
            this->set_LED(color, word.row_begin, col);
        }
    }
    else
    {
        // the word is in one column
        for (uint8_t row = word.row_begin; row < word.row_begin + word.length; row++)
        {
            this->set_LED(color, row, word.col_begin);
        }
    }
}
void Matrix::set_time_in_words_german(const time_t t, const RGB color)
{
    auto time = Date_and_Time(t);
    uint8_t hour = time.tm_hour % 12; // hour is between 0 and 11

    if (time.tm_min < 5)
    {
        // ES IST EINS
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(int_to_word(hour), color);
    }
    else if (time.tm_min < 10)
    {
        // ES IST FÜNF NACH EINS
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(wording::fuenfX, color);
        this->set_word(wording::nach, color);
        this->set_word(int_to_word(hour), color);
    }
    else if (time.tm_min < 15)
    {
        // ES IST ZEHN NACH EINS
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(wording::zehnX, color);
        this->set_word(wording::nach, color);
        this->set_word(int_to_word(hour), color);
    }
    else if (time.tm_min < 20)
    {
        // ES IST FÜNFZEHN NACH EINS
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(wording::fuenfX, color);
        this->set_word(wording::zehnX, color);
        this->set_word(wording::nach, color);
        this->set_word(int_to_word(hour), color);
    }
    else if (time.tm_min < 25)
    {
        // ES IST ZEHN BIS HALB ZWEI
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(wording::zehnX, color);
        this->set_word(wording::bis, color);
        this->set_word(int_to_word(hour + 1), color);
    }
    else if (time.tm_min < 30)
    {
        // ES IST FÜNF BIS HALB ZWEI
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(wording::fuenfX, color);
        this->set_word(wording::bis, color);
        this->set_word(int_to_word(hour + 1), color);
    }
    else if (time.tm_min < 35)
    {
        // ES IST HALB ZWEI
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(wording::halb, color);
        this->set_word(int_to_word(hour + 1), color);
    }
    else if (time.tm_min < 40)
    {
        // ES IST FÜNF NACH HALB ZWEI
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(wording::fuenfX, color);
        this->set_word(wording::nach, color);
        this->set_word(int_to_word(hour + 1), color);
    }
    else if (time.tm_min < 45)
    {
        // ES IST ZEHN NACH HALB ZWEI
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(wording::zehnX, color);
        this->set_word(wording::nach, color);
        this->set_word(int_to_word(hour + 1), color);
    }
    else if (time.tm_min < 50)
    {
        // ES IST FÜNFZEHN BIS ZWEI
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(wording::fuenfX, color);
        this->set_word(wording::zehnX, color);
        this->set_word(wording::bis, color);
        this->set_word(int_to_word(hour + 1), color);
    }
    else if (time.tm_min < 55)
    {
        // ES IST ZEHN BIS ZWEI
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(wording::zehnX, color);
        this->set_word(wording::bis, color);
        this->set_word(int_to_word(hour + 1), color);
    }
    else
    {
        // ES IST FÜNF BIS ZWEI
        this->set_word(wording::es, color);
        this->set_word(wording::ist, color);
        this->set_word(wording::fuenfX, color);
        this->set_word(wording::bis, color);
        this->set_word(int_to_word(hour + 1), color);
    }
}
/*
converts the matrix to a String
*/
String Matrix::to_string() const
{
    String string = "";
    for (uint8_t row = 0; row < rowcount; row++)
    {
        for (uint8_t col = 0; col < colcount; col++)
        {
            if ((this->get_LED(row, col)).max())
            {
                string += " * ";
            }
            else
            {
                string += "   ";
            }
        }
        string += "\n";
    }
    return string;
}
/*
Uses the DEBUG_PRINT() define to print the matrix onto the console
If the Debug modus in release is deactivated, this function does nothing
*/
void Matrix::debug_print() const
{
    DEBUG_PRINT(this->to_string());
}