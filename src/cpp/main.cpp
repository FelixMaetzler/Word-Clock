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

// Funktionsdeklarationen

void jede_sek();
void jede_min();
void jede_std();
void jeden_tag();

/*
Hier wird das aktuelle Datum plus Uhrzeit gespeichert.
Diese wird auch jede Sekunde aktualisiert
*/
volatile time_t datum_isr = 0;
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
  noInterrupts();
  datum_isr = datum;
  interrupts();

  DEBUG_PRINT("es ist gerade: ");
  DEBUG_PRINT(Datum_to_String(datum));
}
// time_t unix = 1648342790; //10 sek vor Sommerzeit 2022
// time_t unix = 1667091590; //10 sek vor Winterzeit 2022

void loop()
{
  // den folgenden Block nicht anfassen!!!
  {
    noInterrupts();
    if (jede_Sek)
    {
      jede_Sek = false;
      datum = datum_isr;
      interrupts();
      // Wird jede Sekunde ausgeführt (ungefähr)
      jede_sek();
    }
    noInterrupts();
    if (jede_Min && !jede_Sek)
    {
      jede_Min = false;
      interrupts();
      // Wird jede Minute ausgeführt (ungefähr)
      // aber nur wenn die Sekunde schon ausgeführt wurde
      jede_min();
    }
    noInterrupts();
    if (jede_Std && !jede_Sek && !jede_Min)
    {
      jede_Std = false;
      interrupts();
      // Wird jede Stunde ausgeführt (ungefähr)
      // aber nur wenn die Sekunde und Minute schon ausgeführt wurde
      jede_std();
    }
    noInterrupts();
    if (jeden_Tag && !jede_Std && !jede_Sek && !jede_Min)
    {
      jeden_Tag = false;
      interrupts();
      // Wird jeden Tag ausgeführt (ungefähr)
      // aber nur wenn die Sekunde, Minute und Stunde schon ausgeführt wurde
      jeden_tag();
    }
    interrupts();
  }
  // bis hier

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
  datum_isr++; // es wird eine Sekunde weitergezählt
  jede_Sek = true;
  if (datum_isr % 60 == 0)
  {
    jede_Min = true;
    if (datum_isr % (60 * 60) == 0)
    {
      jede_Std = true;
      if (datum_isr % (60 * 60 * 24) == 0)
      {
        jeden_Tag = true;
      }
    }
  }
}
/*
Wird (ungefähr) jede Sekunde aufgerufen
*/
void jede_sek()
{
}
/*
Wird (ungefähr) jede Minute aufgerufen
*/
void jede_min()
{
  DEBUG_PRINT(Datum_to_String(datum));
  if (datum % (5 * 60) == 0)
  {
    syncDatum(&datum_isr);
  }
}
/*
Wird (ungefähr) jede Stunde aufgerufen
*/
void jede_std()
{
  DEBUG_PRINT("Test: Jede Stunde");
}
/*
Wird (ungefähr) jeden Tag aufgerufen
*/
void jeden_tag()
{
  DEBUG_PRINT("Test: Jeden Tag");
  syncDatum(&datum_isr);
}