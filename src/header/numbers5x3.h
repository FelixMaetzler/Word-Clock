#include <array>
#include <Arduino.h>

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
ist is constexpr, because the compression is done at Compiletime
*/
constexpr uint16_t arrayToInt(const std::array<std::array<bool, 3>, 5> array)
{
    uint16_t number = 0;
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int i = (int)array.at(row).at(col);
            number = (number << 1) | i;
        }
    }
    return number;
}
/*
this Function decomppresses the 5x3 7-Segment number
this is done at runtime
*/
std::array<std::array<bool, 3>, 5> InttoArray(const uint16_t number)
{
    auto new_number = number;
    std::array<std::array<bool, 3>, 5> array;
    std::array<bool, 15> test;
    for (int i = 14; i >= 0; i--)
    {
        bool rest = new_number % 2;
        new_number /= 2;
        test[i] = rest;
    }
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 3; col++)
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
constexpr std::array<uint16_t, 10> arrayToInt()
{
    return {
        arrayToInt(zero5x3),
        arrayToInt(one5x3),
        arrayToInt(two5x3),
        arrayToInt(three5x3),
        arrayToInt(four5x3),
        arrayToInt(five5x3),
        arrayToInt(six5x3),
        arrayToInt(seven5x3),
        arrayToInt(eight5x3),
        arrayToInt(nine5x3),
    };
}
/*
This is the Array for all 10 5x3 7-Segment Digits in int form
this is done at compiletime
*/
constexpr const auto Numberarray5x3 = arrayToInt();