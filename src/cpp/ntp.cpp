#include "header/release.h"
#include "header/secret.h"
#include "header/ntp.h"
#include "stdlib.h"

#include <TZ.h>

// The "German" weekdays abbreviated. Starting with Sunday
const char *weekday[] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};

const uint16_t localPort = 2390; // local port to listen for UDP packets

IPAddress timeServerIP; // time.nist.gov NTP server address
const char *ntpServerName = "time.nist.gov";

const uint8_t NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

/*
Sets the time zone and time server and connects to the WIFI
*/
void ntp_setup()
{
  configTime(MYTZ, "pool.ntp.org");
  DEBUG_PRINT("Connecting to ");
  DEBUG_PRINT(SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WLAN_Password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    DEBUG(Serial.print("."););
  }
  DEBUG_PRINT("");

  DEBUG_PRINT("WiFi connected");
  DEBUG_PRINT("IP address: ");
  DEBUG_PRINT(WiFi.localIP());

  DEBUG_PRINT("Starting UDP");
  udp.begin(localPort);
  DEBUG_PRINT("Local port: ");
  DEBUG_PRINT(udp.localPort());
}
/*
returns the current date with time
It also already directly respects summer and winter time
*/
time_t get_Date_and_Time()
{
  return time(nullptr);
}
/*
returns the current date with time
It also already directly respects summer and winter time
for this simply the Unix time is transferred
*/
tm get_Date_and_Time(const long long unixtime)
{
  tm date_and_time;
  time_t time = unixtime;
  localtime_r(&time, &date_and_time);
  return date_and_time;
}
/*
This function takes the pointer to the date and returns a string
Example:
So 13.03.2022 09:34:00 Uhr
*/
String Date_and_Time_to_String(const tm *date_and_time)
{
  char buffer[100];
  strftime(buffer, 80, +" %d.%m.%Y  %R:%S Uhr", date_and_time);
  String string = buffer;
  string = weekday[date_and_time->tm_wday] + string;
  return string;
}
/*
Converts a date into a string
Example:
So 13.03.2022 09:34:00 Uhr
*/
String Date_and_Time_to_String(const time_t date_and_time)
{
  tm x = Date_and_Time(date_and_time);
  return Date_and_Time_to_String(&x);
}
/*
converts the Unix time to a correct date
Summer and winter time is already considered
*/
tm Date_and_Time(const time_t unixtime)
{
  tm date_and_time;
  localtime_r(&unixtime, &date_and_time);
  return date_and_time;
}
/*
Synchronizes the internal time with the Internet if it is available.
If not, then the old one simply remains in place
returns if sync was successful or not
ATTENTION!!! This function may take more than 5 seconds!!!
*/
bool syncDatum(volatile time_t *ptr)
{
  time_t date_and_time;
  uint8_t counter = 0;
  /*
  Tries to synchronize the time
  Either until the deviation is less than 10 seconds
  or until he has tried 5 times
  */
  do
  {
    date_and_time = get_Date_and_Time();

    counter++;
    noInterrupts();
    auto akt = *ptr;
    interrupts();
    uint8_t diff = abs(date_and_time - akt);
    if (diff < 10)
    {
      noInterrupts();
      *ptr = date_and_time;
      interrupts();
      DEBUG_PRINT("Sync worked after " + String(counter) + " tries\nOffset was: " + String(diff) + "s");
      return true;
    }
    delay(1000);
  } while (counter < 5);
  return false;
}