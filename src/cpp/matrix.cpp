#include "header/matrix.h"

/*
Standartconstructor
*/
Matrix::Matrix() : matrix(rowcount, std::vector<CRGB>(colcount)) {}

CRGB Matrix::get_LED(int row, int col) const
{
    DEBUG(
        if (row >= rowcount || row < 0 || col >= colcount || col < 0) {
            DEBUG_PRINT("get_LED was called with wrong Parameters (Over or Unterflow");
            return CRGB();
        });
    return matrix.at(row).at(col);
}
void Matrix::set_LED(CRGB led, int row, int col)
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
    int i;
    for (int row = 0; row < rowcount; row++)
    {
        if (row % 2 == 0)
        {
            // from left to right
            for (int col = 0; col < colcount; col++)
            {
                i = row * colcount + col;
                leds[i] = this->get_LED(row, col);
            }
        }
        else
        {
            // from right to left
            int counter = 0;
            for (int col = colcount - 1; col >= 0; col--)
            {
                i = row * colcount + counter;
                leds[i] = this->get_LED(row, col);
                counter++;
            }
        }
    }
#endif

#if LINEBYLINE
    int i;
    for (int row = 0; row < rowcount; row++)
    {
        for (int col = 0; col < colcount; col++)
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
    for (int row = 0; row < rowcount; row++)
    {
        this->set_LED(col.at(row), row, colcount - 1);
    }
}