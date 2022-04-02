#include "header/font7x5.h"

constexpr auto A7x5 = std::array<std::array<bool, 5>, 7>{
    {{0, 1, 1, 1, 0},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1}}};
constexpr auto B7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 0},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 0},
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 0}}};
constexpr auto C7x5 = std::array<std::array<bool, 5>, 7>{
    {{0, 1, 1, 1, 1},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {0, 1, 1, 1, 1}}};
constexpr auto D7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 0},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 0}}};
constexpr auto E7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 1}}};
constexpr auto F7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0}}};
constexpr auto G7x5 = std::array<std::array<bool, 5>, 7>{
    {{0, 1, 1, 1, 1},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {0, 1, 1, 1, 0}}};
constexpr auto H7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1}}};
constexpr auto I7x5 = std::array<std::array<bool, 5>, 7>{
    {{0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0}}};
constexpr auto J7x5 = std::array<std::array<bool, 5>, 7>{
    {{0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {0, 1, 1, 1, 0}}};
constexpr auto K7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 0, 0, 0, 1},
     {1, 0, 0, 1, 0},
     {1, 0, 1, 0, 0},
     {1, 1, 0, 0, 0},
     {1, 0, 1, 0, 0},
     {1, 0, 0, 1, 0},
     {1, 0, 0, 0, 1}}};
constexpr auto L7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 1}}};
constexpr auto M7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 0, 0, 0, 1},
     {1, 1, 0, 1, 1},
     {1, 0, 1, 0, 1},
     {1, 0, 1, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1}}};
constexpr auto N7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 0, 0, 1},
     {1, 0, 1, 0, 1},
     {1, 0, 0, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1}}};
constexpr auto O7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1}}};
constexpr auto P7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 0},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0}}};
constexpr auto Q7x5 = std::array<std::array<bool, 5>, 7>{
    {{0, 1, 1, 1, 0},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 1, 0, 1},
     {0, 1, 1, 1, 0},
     {0, 0, 0, 0, 1}}};
constexpr auto R7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 0},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 0},
     {1, 0, 1, 0, 0},
     {1, 0, 0, 1, 0},
     {1, 0, 0, 0, 1}}};
constexpr auto S7x5 = std::array<std::array<bool, 5>, 7>{
    {{0, 1, 1, 1, 1},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {1, 1, 1, 1, 0}}};
constexpr auto T7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 1},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0}}};
constexpr auto U7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1}}};
constexpr auto V7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {0, 1, 0, 1, 0},
     {0, 0, 1, 0, 0}}};
constexpr auto W7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 1, 0, 1},
     {1, 0, 1, 0, 1},
     {1, 1, 0, 1, 1},
     {1, 0, 0, 0, 1}}};
constexpr auto X7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {0, 1, 0, 1, 0},
     {0, 0, 1, 0, 0},
     {0, 1, 0, 1, 0},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1}}};
constexpr auto Y7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {0, 1, 0, 1, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0}}};
constexpr auto Z7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 1, 0},
     {0, 0, 1, 0, 0},
     {0, 1, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 1}}};
constexpr auto zero7x5 = std::array<std::array<bool, 5>, 7>{
    {{0, 1, 1, 1, 0},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {0, 1, 1, 1, 0}}};
constexpr auto one7x5 = std::array<std::array<bool, 5>, 7>{
    {{0, 0, 1, 0, 0},
     {0, 1, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0},
     {0, 0, 1, 0, 0}}};
constexpr auto two7x5 = std::array<std::array<bool, 5>, 7>{
    {{0, 1, 1, 1, 0},
     {1, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 1, 1, 0},
     {1, 1, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 1}}};
constexpr auto three7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 0},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {0, 1, 1, 1, 0},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {1, 1, 1, 1, 0}}};
constexpr auto four7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1}}};
constexpr auto five7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 0},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {1, 1, 1, 1, 0}}};
constexpr auto six7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 1},
     {1, 0, 0, 0, 0},
     {1, 0, 0, 0, 0},
     {1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {1, 1, 1, 1, 1}}};
constexpr auto seven7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1}}};
constexpr auto eight7x5 = std::array<std::array<bool, 5>, 7>{
    {{1, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {0, 1, 1, 1, 0},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {0, 1, 1, 1, 0}}};
constexpr auto nine7x5 = std::array<std::array<bool, 5>, 7>{
    {{0, 1, 1, 1, 1},
     {1, 0, 0, 0, 1},
     {1, 0, 0, 0, 1},
     {0, 1, 1, 1, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1},
     {0, 0, 0, 0, 1}}};

/*
Helperfunction to compress a 7x5 Pixelarray into an int
this way you store the Information in 8 Byte instead of 35
It is constexpr, because the compression is done at Compiletime
*/
constexpr uint64_t compress7x5(const std::array<std::array<bool, 5>, 7> array)
{
    uint64_t number = 0;
    for (uint8_t row = 0; row < 7; row++)
    {
        for (uint8_t col = 0; col < 5; col++)
        {
            bool i = array.at(row).at(col);
            number = (number << 1) | i;
        }
    }
    return number;
}
/*
this function wraps all 26 7x5 capital letter into one big int array
this is done at compiletime
*/
constexpr const std::array<uint64_t, 26> compressCapitalLetters7x5()
{
    return {
        compress7x5(A7x5),
        compress7x5(B7x5),
        compress7x5(C7x5),
        compress7x5(D7x5),
        compress7x5(E7x5),
        compress7x5(F7x5),
        compress7x5(G7x5),
        compress7x5(H7x5),
        compress7x5(I7x5),
        compress7x5(J7x5),
        compress7x5(K7x5),
        compress7x5(L7x5),
        compress7x5(M7x5),
        compress7x5(N7x5),
        compress7x5(O7x5),
        compress7x5(P7x5),
        compress7x5(Q7x5),
        compress7x5(R7x5),
        compress7x5(S7x5),
        compress7x5(T7x5),
        compress7x5(U7x5),
        compress7x5(V7x5),
        compress7x5(W7x5),
        compress7x5(X7x5),
        compress7x5(Y7x5),
        compress7x5(Z7x5)};
}
/*
this function wraps all 10 7x5 Digits into one big int array
this is done at compiletime
*/
constexpr const std::array<uint64_t, 10> compressNumbers7x5()
{
    return {
        compress7x5(zero7x5),
        compress7x5(one7x5),
        compress7x5(two7x5),
        compress7x5(three7x5),
        compress7x5(four7x5),
        compress7x5(five7x5),
        compress7x5(six7x5),
        compress7x5(seven7x5),
        compress7x5(eight7x5),
        compress7x5(nine7x5)};
}
/*
stores the nubers 0-9
zero is stored at index 0 etc
this variable is computed at compiletime
*/
constexpr auto Numbers7x5 = compressNumbers7x5();
/*
stores the nubers 0-9
zero is stored at index 0 etc
this variable is computed at compiletime
*/
constexpr auto CapitalLetters7x5 = compressCapitalLetters7x5();

/*
this Function decompresses the 7x5 pixel array
this is done at runtime
*/
std::array<std::array<bool, 5>, 7> decompress7x5(const uint64_t number)
{
    //Here is missing the numbers
    //FIX!!!

    auto new_number = CapitalLetters7x5[number];
    std::array<std::array<bool, 5>, 7> array;
    std::array<bool, 35> test;
    for (int8_t i = 34; i >= 0; i--)
    {
        bool rest = new_number % 2;
        new_number /= 2;
        test[i] = rest;
    }
    for (uint8_t row = 0; row < 7; row++)
    {
        for (uint8_t col = 0; col < 5; col++)
        {
            array.at(row).at(col) = test[row * 5 + col];
        }
    }
    return array;
}
