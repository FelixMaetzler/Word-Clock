

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ctime>

void ntp_setup();
tm get_Datum(const long long);
time_t get_Datum();
String Datum_to_String(const tm *);
String Datum_to_String(const time_t);
tm Datum(const time_t);
bool syncDatum(volatile time_t *);