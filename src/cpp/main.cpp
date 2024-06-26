#include "header/release.h"

#include <Arduino.h>

#include "header/LED.h"
#include "header/ntp.h"
#include "header/matrix.h"

#include "header/webserver.h"

uint8_t offset = 0;
uint16_t counter = 0;
uint8_t led_count = 15;
String Scrolling_Text = "";
Matrix matrix;

extern AsyncWebSocket ws;

bool modeWordClock = true;
bool modeDigitalClock = false;
bool modeScrollingText = false;

RGB color = RGB(255);

// this variables get set every sec/min/h/d
// because of this, youc can do things every sec/min/h/d in the loop()
volatile uint8_t counter10ms = 0;
/*
DONT USE THIS VARIABLE!!!
get set every second
Use every_10ms() instead
*/
volatile bool every_10Ms = false;
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

void every_10ms();
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

Strip strip;

/*
This is the ISR, that get executed every second
*/
void IRAM_ATTR onTime10ms();

String ledState;

void setup()
{
  Serial.begin(115200);
  ntp_setup();
  websocket_Setup();
  webserver_Setup();

  strip.begin();
  timer1_attachInterrupt(onTime10ms); // Add ISR Function
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_LOOP);
  timer1_write(5 * 1e4); // 10 ms
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
  MDNS.update();
  // DONT TOUCH THE FOLLOWING BLOCK
  {
    noInterrupts();
    if (every_10Ms)
    {
      every_10Ms = false;
      interrupts();
      // gets executed roughly every 10 ms
      every_10ms();
    }
    noInterrupts();
    if (every_Sec && !every_10Ms)
    {
      every_Sec = false;
      time_and_date = time_and_date_isr;
      interrupts();
      // gets executed roughly every second
      every_sec();
    }
    noInterrupts();
    if (every_Min && !every_10Ms && !every_Sec)
    {
      every_Min = false;
      interrupts();
      // gets executed roughly every minute
      // but only if second is already executed
      every_min();
    }
    noInterrupts();
    if (every_H && !every_10Ms && !every_Sec && !every_Min)
    {
      every_H = false;
      interrupts();
      // gets executed roughly every hour
      // but only if second and minute is already executed
      every_hour();
    }
    noInterrupts();
    if (every_D && !every_10Ms && !every_H && !every_Sec && !every_Min)
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
}
// HW Timer1 Interrupt. Gets executed every second
void IRAM_ATTR onTime10ms()
{
  every_10Ms = true;
  counter10ms++;
  if (counter10ms == 100)
  {
    counter10ms = 0;
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
}
/*
gets executed roughly every 10 ms
Note: if the project is too busy, it can happen,
that single 10ms can be skipped.
*/
void every_10ms()
{
  if (modeScrollingText)
  {
    if (offset == 25)
    {
      offset = 0;

      counter = matrix.scrolling_text(counter, Scrolling_Text, color);
      // matrix.debug_print();
      matrix.matrix_to_LEDArray(&strip);
      strip.show();
    }
    offset++;
  }
}
/*
gets executed roughly every second
Note: if the project is too busy, it can happen,
that single seconds can be skiped.
*/
void every_sec()
{
  ws.cleanupClients();
  if (time_and_date % 5 == 0)
  {
    if (modeDigitalClock)
    {
      matrix.clear();

      // matrix.set_LED(RgbColor(255), 0, 0);
      // matrix.set_digital_clock(Date_and_Time(time_and_date), std::array<RGB, 4> {RGB(10,0,0), RGB(0,10,0), RGB(0,0,10), RGB(10)});
      matrix.set_digital_clock(Date_and_Time(time_and_date), {RGB(200, 0, 0), RGB(0, 200, 0), RGB(0, 0, 200), RGB(200, 0, 200)});

      matrix.debug_print();
      matrix.matrix_to_LEDArray(&strip); // to to;
      strip.show();
    }
    if (modeWordClock)
    {
      matrix.clear();
      matrix.set_time_in_words_german(time_and_date, color);
      matrix.matrix_to_LEDArray(&strip); // to to;
      strip.set_dots((time_and_date / 60) % 5, color);
      strip.show();
    }
  }
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