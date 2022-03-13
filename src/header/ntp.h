

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ctime>

void ntp_setup();
unsigned long get_Unix_time();
void sendNTPpacket(IPAddress &);
void display_time();
tm get_Datum(const long long);
time_t get_Datum();
String Datum_to_String(const tm *);
String Datum_to_String(const time_t);
tm Datum(const time_t);
