#include "header/LED.h"

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(num_leds);
void led_setup()
{
    strip.Begin();
    strip.Show();
    for (int i = 0; i < 300; i++)//to do
    {
        strip.SetPixelColor(i, RgbColor(0));
    }
    strip.Show();
}
