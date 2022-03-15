

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ctime>

void ntp_setup();
tm get_Date_and_Time(const long long);
time_t get_Date_and_Time();
String Date_and_Time_to_String(const tm *);
String Date_and_Time_to_String(const time_t);
tm Date_and_Time(const time_t);
bool syncDatum(volatile time_t *);