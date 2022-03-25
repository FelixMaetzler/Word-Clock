#include "header/RGB.h"
#include "header/HSL.h"

/*
constructs an HSL Color with the three parameters
all parameters have to be between 0 and 255
*/
HSL::HSL(uint8_t h, uint8_t s, uint8_t l)
{
    this->h = h;
    this->s = s;
    this->l = l;
}
/*
returns the Hue value
*/
uint8_t HSL::get_h() const
{
    return this->h;
}
/*
returns the Saturation value
*/
uint8_t HSL::get_s() const
{
    return this->s;
}
/*
returns the Lightness value
*/
uint8_t HSL::get_l() const
{
    return this->l;
}
/*
sets the Hue value
this value has to be between 0 - 255
*/
void HSL::set_h(const uint8_t h)
{
    this->h = h;
}
/*
sets the Saturation value
this value has to be between 0 - 255
*/
void HSL::set_s(const uint8_t s)
{
    this->s = s;
}
/*
sets the Lightness value
this value has to be between 0 - 255
*/
void HSL::set_l(const uint8_t l)
{
    this->l = l;
}
/*
Converts an RGB value to an HSL value
*/
HSL::HSL(const RGB rgb)
{
    // https://en.wikipedia.org/wiki/HSL_and_HSV

    const double r = rgb.get_r() / 255.0; // R value scaled from 0 to 1
    const double g = rgb.get_g() / 255.0; // G value scaled from 0 to 1
    const double b = rgb.get_b() / 255.0; // B value scaled from 0 to 1

    const double xmin = min(r, min(g, b)); // lowest RGB value from 0 to 1
    const double v = max(r, max(g, b));    // highest RGB value from 0 to 1
    const double c = v - xmin;             // difference Between the highest and lowest RGB value from 0 to 1
    const double l = 0.5 * (v + xmin);     // mean between the lowest and highest value from 0 to 1
    double h = 0;
    double s = 0;
    if (v == r)
    {
        h = 60.0 * ((g - b) / c);
    }
    else if (v == g)
    {
        h = 60.0 * (2 + ((b - r) / c));
    }
    else
    {
        h = 60.0 * (4 + ((r - g) / c));
    }
    if (!(l == 0.0 || l == 1.0))
    {
        s = (v - l) / min(l, 1 - l);
    }
    this->h = h * (255.0 / 360.0); // scaling from 0 to 255
    this->s = s * 255.0;           // scaling from 0 to 255
    this->l = l * 255.0;           // scaling from 0 to 255
}
/*
This function converts the HSL value to an NEopixel HSL Color
*/
HslColor HSL::convert() const
{
    return HslColor(this->get_h() / 255.0, this->get_s() / 255.0, this->get_l() / 255.0);
}