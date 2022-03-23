#include "header/helperfunctions.h"

/*
converts a uint8_t value between the two boundaries to a double inbetween two boundaries
*/
double map(const uint8_t value,const uint8_t lower_boundIN,const uint8_t upper_boundIN, const double lower_boundOUT, const double upper_boundOUT){
    return (((double(value) - lower_boundIN) * (upper_boundOUT -lower_boundOUT)) / double(upper_boundIN - lower_boundIN)) + lower_boundOUT;
}
/*
converts a uint8_t into an double between 0.0 an 1.0
*/
double map(const uint8_t value){
    return double(value) / 255.0;
}