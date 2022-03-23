#include "header/release.h"

#include <Arduino.h>

#include "header/LED.h"
#include "header/ntp.h"
#include "header/matrix.h"

// this variables get set every sec/min/h/d
// because of this, youc can do things every sec/min/h/d in the loop()

/*
DONT USE THIS VARIABLE!!!
get set every second
Use every_sec() instead
*/
volatile bool every_Sec = false;
/*
DONT USE THIS VARIABLE!!!
get set every minute
Use every_min() instead
*/
volatile bool every_Min = false;
/*
DONT USE THIS VARIABLE!!!
get set every hour
Use every_hour() instead
*/
volatile bool every_H = false;
/*
DONT USE THIS VARIABLE!!!
get set every day
Use every_day() instead
*/
volatile bool every_D = false;

// function declaration

void every_sec();
void every_min();
void every_hour();
void every_day();

/*
DONT USE THIS VARIABLE!!!
this stores the current date and time
this gets updated every second in an ISR
this can lead to fatal errors in your program
*/
volatile time_t time_and_date_isr = 0;
/*
this stores the current date and time
this gets updated roughly every second
you should only use this for your calculations!!!
*/
time_t time_and_date = 0;
/*
stores the LED-Matrix in an array
is needed for the FastLED libary
*/

extern NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip;

/*
This is the ISR, that get executed every second
*/
void IRAM_ATTR onTime1s();

void setup()
{
  Serial.begin(115200);
  ntp_setup();
  led_setup();
  timer1_attachInterrupt(onTime1s); // Add ISR Function
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  timer1_write(5 * 1e6); // 1 sec
  // this loop tries to get the latest time and date
  do
  {
    time_and_date = get_Date_and_Time(); // If get_Date_and_Time() do not get the latest date and time, it returns 0 (or another "small" number)
    delay(100);
  } while (time_and_date < 1e6); // If it is not a small number, it succeeded

  noInterrupts();
  time_and_date_isr = time_and_date;
  interrupts();

  DEBUG_PRINT("It is: ");
  DEBUG_PRINT(Date_and_Time_to_String(time_and_date));
  // time_t unix = 1648342790; //10 sec before Summertime 2022
  // time_t unix = 1667091590; //10 sec before wintertime 2022
}

void loop()
{

  for (uint8_t i = 0; i < 10; i++)
  {
    strip.SetPixelColor(i, RgbColor(20));
    strip.Show();
    strip.SetPixelColor(i, RgbColor(0));
    delay(200);
  }
  for (uint8_t i = 8; i > 0; i--)
  {
    strip.SetPixelColor(i, RgbColor(20));
    strip.Show();
    strip.SetPixelColor(i, RgbColor(0));
    delay(200);
  }

  // DONT TOUCH THE FOLLOWING BLOCK
  {
    noInterrupts();
    if (every_Sec)
    {
      every_Sec = false;
      time_and_date = time_and_date_isr;
      interrupts();
      // gets executed roughly every second
      every_sec();
    }
    noInterrupts();
    if (every_Min && !every_Sec)
    {
      every_Min = false;
      interrupts();
      // gets executed roughly every minute
      // but only if second is already executed
      every_min();
    }
    noInterrupts();
    if (every_H && !every_Sec && !every_Min)
    {
      every_H = false;
      interrupts();
      // gets executed roughly every hour
      // but only if second and minute is already executed
      every_hour();
    }
    noInterrupts();
    if (every_D && !every_H && !every_Sec && !every_Min)
    {
      every_D = false;
      interrupts();
      // gets executed roughly every day
      // but only if second, minute and hour is already executed
      every_day();
    }
    interrupts();
  }
  // UNTIL HERE

  delay(100);
}
// HW Timer1 Interrupt. Gets executed every second
void IRAM_ATTR onTime1s()
{
  time_and_date_isr++; // count one second
  every_Sec = true;
  if (time_and_date_isr % 60 == 0)
  {
    every_Min = true;
    if (time_and_date_isr % (60 * 60) == 0)
    {
      every_H = true;
      if (time_and_date_isr % (60 * 60 * 24) == 0)
      {
        every_D = true;
      }
    }
  }
}
/*
gets executed roughly every second
Note: if the project is too busy, it can happen,
that single seconds can be skiped.
*/
void every_sec()
{
}
/*
gets executed roughly every minute
Note: if the project is too busy, it can happen,
that single minutes can be skiped.
This is highly unlikely, because the project has to be very busy
*/
void every_min()
{
  DEBUG_PRINT(Date_and_Time_to_String(time_and_date));
  if (time_and_date % (5 * 60) == 0)
  {
    syncDatum(&time_and_date_isr);
  }
}
/*
gets executed roughly every hour
Note: if the project is too busy, it can happen,
that single hours can be skiped.
This is highly unlikely, because the project has to be very, very busy
*/
void every_hour()
{
  DEBUG_PRINT("Test: every hour");
}
/*
gets executed roughly every day
Note: if the project is too busy, it can happen,
that single days can be skiped.
This is highly unlikely, because the project has to be very, very, very busy
*/
void every_day()
{
  DEBUG_PRINT("Test: every day");
  syncDatum(&time_and_date_isr);
}