#include "header/LED.h"

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(num_leds);
void led_setup()
{
    strip.Begin();
    strip.Show();
    for (int i = 0; i < 300; i++) // to do
    {
        strip.SetPixelColor(i, RgbColor(0));
    }
    strip.Show();
}
void hue(NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> *strip, const uint8_t count, const uint8_t offset)
{
    for (uint8_t i = 0; i < count; i++)
    {
        strip->SetPixelColor(i, HsbColor(map((i+offset)%256), 1, map(2)));
    }
    strip->Show();
}


