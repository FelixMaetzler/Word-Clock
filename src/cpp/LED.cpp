#include "header/LED.h"

/*
shows the LEDs
*/
void Strip::show()
{
    this->strip.Show();
}
/*
sets the i-th LED to a spezific color
*/
void Strip::set_led(uint16_t index, RGB color)
{
    strip.SetPixelColor(index, color.convert());
}
/*
cycles through the hue color
begin_index
led_count
offset: coloroffset for the cycle
*/
void Strip::rainbow(uint16_t begin_index, uint16_t led_count, uint8_t offset)
{
    for (uint16_t i = begin_index; i < begin_index + led_count; i++)
    {
        this->set_led(i, HSL(i * 10 + offset, 255, 10));
    }
}
/*
initiates the LED Strip
*/
void Strip::begin()
{
    this->strip.Begin();
    this->strip.Show();
    for (int i = 0; i < 300; i++) // to do
    {
        this->set_led(i, RGB(0));
    }
    this->strip.Show();
}
void Strip::clear(){
    for (uint16_t i = 0; i < num_leds; i++)
    {
        this->strip.ClearTo(RGB(0).convert(), 0, num_leds - 1);
    }
    
}
void Strip::set_dots(uint8_t count, RGB color){
    uint16_t indexfirstdot = colcount * rowcount;
    for (uint16_t i = 0; i < 4; i++)
    {
        this->set_led(indexfirstdot + i, RGB(0));
    }
    switch (count)
    {
    case 4: this->set_led(indexfirstdot + 3, color);
    case 3: this->set_led(indexfirstdot + 2, color);
    case 2: this->set_led(indexfirstdot + 1, color);
    case 1: this->set_led(indexfirstdot + 0, color);
    }
}