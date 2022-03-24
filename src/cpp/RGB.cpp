#include "header/RGB.h"
#include "header/HSL.h"

/*
constructs an RGB value with the three parameters
all parameters has to be between 0 and 255
*/
RGB::RGB(uint8_t r, uint8_t g, uint8_t b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}
/*
returns the R value
*/
uint8_t RGB::get_r() const
{
    return this->r;
}
/*
returns the G value
*/
uint8_t RGB::get_g() const
{
    return this->g;
}
/*
returns the B value
*/
uint8_t RGB::get_b() const
{
    return this->b;
}
/*
sets the R value
this value has to be between 0 and 255
*/
void RGB::set_r(const uint8_t r)
{
    this->r = r;
}
/*
sets the G value
this value has to be between 0 and 255
*/
void RGB::set_g(const uint8_t g)
{
    this->g = g;
}
/*
sets the B value
this value has to be between 0 and 255
*/
void RGB::set_b(const uint8_t b)
{
    this->b = b;
}
/*
constructs a RGB color from a HSL color
*/
RGB::RGB(const HSL hsl)
{
    // https://en.wikipedia.org/wiki/HSL_and_HSV

    double h = hsl.get_h();
    double s = hsl.get_s();
    double l = hsl.get_l();
    h = (h / 255.0) * 360.0;
    s /= 255.0;
    l /= 255.0;
    for (uint8_t n = 0; n < 9; n += 4)
    {
        double k = fmod(n + h / 30.0, 12);
        double a = s * min(l, 1 - l);
        double f = l - a * std::max(-1.0, std::min(k - 3, std::min(9.0 - k, 1.0)));
        if (n == 0)
        {
            this->r = f * 255.0;
        }
        else if (n == 4)
        {
            this->g = f * 255.0;
        }
        else
        {
            this->b = f * 255.0;
        }
    }
}
/*
converts a RGB color to a Neopixel RgbColor
*/
RgbColor RGB::convert() const
{
    return RgbColor(this->get_r(), this->get_g(), this->get_b());
}
/*
constructs a RGB color
sets all three colors to the one parameter
*/
RGB::RGB(uint8_t color)
{
    this->r = color;
    this->g = color;
    this->b = color;
}
/*
returns the highest value of RGB
*/
uint8_t RGB::max() const
{
    return std::max(this->get_r(), std::max(this->get_g(), this->get_b()));
}
/*
Constructs an RGB color
and initialise all to 0
*/
RGB::RGB()
{
    this->r = 0;
    this->g = 0;
    this->b = 0;
}