#include "header/release.h"

#include <Arduino.h>

#include "header/LED.h"
#include "header/ntp.h"

// Diese werden jede Sek/Min/Std gesetzt
// Somit können in loop() Dinge einmal pro Sek/Min/Std ausgeführt werden

volatile bool jede_Sek = false;  // wird jede Sekunde gesetzt
volatile bool jede_Min = false;  // wird jede Minute gesetzt
volatile bool jede_Std = false;  // wird jede Stunde gesetzt
volatile bool jeden_Tag = false; // wird jeden Tag gesetzt
/*
Hier wird das aktuelle Datum plus Uhrzeit gespeichert.
Diese wird auch jede Sekunde aktualisiert
*/
time_t datum = 0;

CRGB leds[NUM_LEDS];

void IRAM_ATTR onTime1s();

void setup()
{
  Serial.begin(115200);
  ntp_setup();
  led_setup();
  timer1_attachInterrupt(onTime1s); // Add ISR Function
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  timer1_write(5 * 1e6); // 1 sek
  // hier wird versucht das aktuelle Datum+Uhrzeit abzurufen
  do
  {
    datum = get_Datum(); // Wenn es nicht gelingt, wird null zurückgeben
    delay(100);
  } while (datum < 1e6);

  DEBUG_PRINT("es ist gerade: ");
  DEBUG_PRINT(Datum_to_String(datum));
}
// time_t unix = 1648342790; //10 sek vor Sommerzeit 2022
// time_t unix = 1667091590; //10 sek vor Winterzeit 2022

void loop()
{
  if (jede_Sek)
  {
    jede_Sek = false;
    // Wird jede Sekunde ausgeführt (ungefähr)
  }
  if (jede_Min && !jede_Sek)
  {
    jede_Min = false;
    // Wird jede Minute ausgeführt (ungefähr)
    // aber nur wenn die Sekunde schon ausgeführt wurde
    DEBUG_PRINT(Datum_to_String(datum));
  }
  if (jede_Std && !jede_Sek && !jede_Min)
  {
    jede_Std = false;
    // Wird jede Stunde ausgeführt (ungefähr)
    // aber nur wenn die Sekunde und Minute schon ausgeführt wurde
    DEBUG_PRINT("Test: Jede Stunde");
  }
  if (jeden_Tag && !jede_Std && !jede_Sek && !jede_Min)
  {
    jeden_Tag = false;
    // Wird jeden Tag ausgeführt (ungefähr)
    // aber nur wenn die Sekunde, Minute und Stunde schon ausgeführt wurde
    DEBUG_PRINT("Test: Jeden Tag");
  }

  delay(100);

  /*
  for (int dot = 0; dot < NUM_LEDS; dot++)
  {
    leds[dot] = CRGB::BlueViolet;
    leds[dot] &= 20;
    FastLED.show();
    // clear this led for the next time around the loop
    leds[dot] = CRGB::Black;
    delay(30);

  }
  */
}
// HW Timer1 Interrupt. wird jede sek aufgerufen
void IRAM_ATTR onTime1s()
{
  datum++; // es wird eine Sekunde weitergezählt
  auto zeit = Datum(datum);
  jede_Sek = true;
  if (zeit.tm_sec == 0)
  {
    jede_Min = true;
    if (zeit.tm_min == 0)
    {
      jede_Std = true;
      if (zeit.tm_hour == 0)
      {
        jeden_Tag = true;
      }
    }
  }
}