#include "header/numbers5x3.h"

constexpr auto zero5x3 = std::array<std::array<bool, 3>, 5>{
    {{1, 1, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 1, 1}}};
constexpr auto one5x3 = std::array<std::array<bool, 3>, 5>{
    {{0, 0, 1},
     {0, 0, 1},
     {0, 0, 1},
     {0, 0, 1},
     {0, 0, 1}}};
constexpr auto two5x3 = std::array<std::array<bool, 3>, 5>{
    {{1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1}}};
constexpr auto three5x3 = std::array<std::array<bool, 3>, 5>{
    {{1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}}};
constexpr auto four5x3 = std::array<std::array<bool, 3>, 5>{
    {{1, 0, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1}}};
constexpr auto five5x3 = std::array<std::array<bool, 3>, 5>{
    {{1, 1, 1},
     {1, 0, 0},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}}};
constexpr auto six5x3 = std::array<std::array<bool, 3>, 5>{
    {{1, 1, 1},
     {1, 0, 0},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}}};
constexpr auto seven5x3 = std::array<std::array<bool, 3>, 5>{
    {{1, 1, 1},
     {0, 0, 1},
     {0, 0, 1},
     {0, 0, 1},
     {0, 0, 1}}};
constexpr auto eight5x3 = std::array<std::array<bool, 3>, 5>{
    {{1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}}};
constexpr auto nine5x3 = std::array<std::array<bool, 3>, 5>{
    {{1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}}};

     /*
Helperfunction to compress a 5x3 7-Segment number into an int
this way you store the information in 2 Byte instead of 15
it is constexpr, because the compression is done at Compiletime
*/
constexpr uint16_t compress5x3(const std::array<std::array<bool, 3>, 5> array)
{
    uint16_t number = 0;
    for (uint8_t row = 0; row < 5; row++)
    {
        for (uint8_t col = 0; col < 3; col++)
        {
            bool i = array.at(row).at(col);
            number = (number << 1) | i;
        }
    }
    return number;
}
/*
this Function decompresses the 5x3 7-Segment number
this is done at runtime
*/
std::array<std::array<bool, 3>, 5> decompress5x3(const uint16_t number)
{
    auto new_number = number;
    std::array<std::array<bool, 3>, 5> array;
    std::array<bool, 15> test;
    for (uint8_t i = 14; i >= 0; i--)
    {
        bool rest = new_number % 2;
        new_number /= 2;
        test[i] = rest;
    }
    for (uint8_t row = 0; row < 5; row++)
    {
        for (uint8_t col = 0; col < 3; col++)
        {
            array.at(row).at(col) = test[row * 3 + col];
        }
    }
    return array;
}
/*
this function wraps all 10 5x3 7-Segment Digits into one big int array
this is done at compiletime
*/
constexpr std::array<uint16_t, 10> compress5x3()
{
    return {
        compress5x3(zero5x3),
        compress5x3(one5x3),
        compress5x3(two5x3),
        compress5x3(three5x3),
        compress5x3(four5x3),
        compress5x3(five5x3),
        compress5x3(six5x3),
        compress5x3(seven5x3),
        compress5x3(eight5x3),
        compress5x3(nine5x3),
    };
}
/*
This is the Array for all 10 5x3 7-Segment Digits in int form
this is done at compiletime
*/
constexpr const auto Numbers5x3 = compress5x3();