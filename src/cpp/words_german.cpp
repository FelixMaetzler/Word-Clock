#include "header/words_german.h"

/*
The following code is for a 10x10 Matrix with german wordings
  0 1 2 3 4 5 6 7 8 9
0 E S   I S T
1 F Ü N F Z E H N
2 N A C H B I S
3 D R E I H A L B
4 V I E R T E L
5 E I N S A S E C H S
6 Z W E I C Z E H N E
7 N E U N H D R E I L
8 F Ü N F T Z W Ö L F
9 S I E B E N V I E R
*/

constexpr auto Word_es = encode(0, 0, 2, true);
constexpr auto Word_ist = encode(0, 3, 3, true);
constexpr auto Word_fuenfX = encode(1, 0, 4, true);
constexpr auto Word_zehnX = encode(1, 4, 4, true);
constexpr auto Word_nach = encode(2, 0, 4, true);
constexpr auto Word_bis = encode(2, 4, 3, true);
constexpr auto Word_dreiv = encode(3, 0, 4, true);
constexpr auto Word_halb = encode(3, 4, 4, true);
constexpr auto Word_viertel = encode(4, 0, 7, true);
constexpr auto Word_eins = encode(5, 0, 4, true);
constexpr auto Word_sechs = encode(5, 5, 5, true);
constexpr auto Word_zwei = encode(6, 0, 4, true);
constexpr auto Word_zehn = encode(6, 5, 4, true);
constexpr auto Word_neun = encode(7, 0, 4, true);
constexpr auto Word_drei = encode(7, 5, 4, true);
constexpr auto Word_fuenf = encode(8, 0, 4, true);
constexpr auto Word_zwoelf = encode(8, 5, 5, true);
constexpr auto Word_sieben = encode(9, 0, 6, true);
constexpr auto Word_vier = encode(9, 6, 4, true);
constexpr auto Word_acht = encode(5, 4, 4, false);
constexpr auto Word_elf = encode(6, 9, 3, false);

constexpr std::array<encode, 21> to_array(){
return std::array<encode, 21>{
    Word_es,
    Word_ist,
    Word_fuenfX,
    Word_zehnX,
    Word_nach,
    Word_bis,
    Word_dreiv,
    Word_halb,
    Word_viertel,
    Word_eins,
    Word_sechs,
    Word_zwei,
    Word_zehn,
    Word_neun,
    Word_drei,
    Word_fuenf,
    Word_zwoelf,
    Word_sieben,
    Word_vier,
    Word_acht,
    Word_elf,
};
}
/*Test 123*/
constexpr  auto Words = to_array();

/*
constexpr const std::array<encode, 21> Words{
    Word_es,
    Word_ist,
    Word_fuenfX,
    Word_zehnX,
    Word_nach,
    Word_bis,
    Word_dreiv,
    Word_halb,
    Word_viertel,
    Word_eins,
    Word_sechs,
    Word_zwei,
    Word_zehn,
    Word_neun,
    Word_drei,
    Word_fuenf,
    Word_zwoelf,
    Word_sieben,
    Word_vier,
    Word_acht,
    Word_elf,
};
*/

/*
converts the hour to the right wording enum
the index is the wording
0 gets wraped to 12
*/
wording int_to_word(const uint8_t hour)
{
    DEBUG(if (!(0 <= hour && hour <= 12)) {
        DEBUG_PRINT("int_to_wording gets a false value (Over or Underflow");
    });
    uint8_t hours = hour % 12;
    switch (hours)
    {
    case 0:
        return wording::zwoelf;
    case 1:
        return wording::eins;
    case 2:
        return wording::zwei;
    case 3:
        return wording::drei;
    case 4:
        return wording::vier;
    case 5:
        return wording::fuenf;
    case 6:
        return wording::sechs;
    case 7:
        return wording::sieben;
    case 8:
        return wording::acht;
    case 9:
        return wording::neun;
    case 10:
        return wording::zehn;
    case 11:
        return wording::elf;
    }
    return wording::bis;//to do
}
encode to_word(uint8_t index){
    return Words.at(index);
}