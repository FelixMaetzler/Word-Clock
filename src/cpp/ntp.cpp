#include "header/release.h"
#include "header/secret.h"
#include "header/ntp.h"

#include <TZ.h>

#define MYTZ TZ_Europe_Berlin
const char* wochentag[] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};

const unsigned int localPort = 2390; // local port to listen for UDP packets

IPAddress timeServerIP; // time.nist.gov NTP server address
const char *ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

/*
Setzt die Zeitzone und den Zeitserver und verbindet sich mit dem WLAN
*/
void ntp_setup()
{
  configTime(MYTZ, "pool.ntp.org");
  DEBUG_PRINT("Connecting to ");
  DEBUG_PRINT(SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, WLAN_Passwort);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  DEBUG_PRINT("");

  DEBUG_PRINT("WiFi connected");
  DEBUG_PRINT("IP address: ");
  DEBUG_PRINT(WiFi.localIP());

  DEBUG_PRINT("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  DEBUG_PRINT(udp.localPort());
}
/*
gibt das aktuelle Datum mit Uhrzeit zurück
Es beachtet auch schon direkt Sommer- und Winterzeit
*/
time_t get_Datum()
{
  /*
  tm datum;
  time_t zeit = time(nullptr);
  localtime_r(&zeit, &datum);
  return datum;
*/
return time(nullptr);
}
/*
gibt das aktuelle Datum mit Uhrzeit zurück
Es beachtet auch schon direkt Sommer- und Winterzeit
dafür wird einfach die Unixzeit übergeben
*/
tm get_Datum(const long long unix)
{
  tm datum;
  time_t zeit = unix;
  localtime_r(&zeit, &datum);
  return datum;
}
/*
Diese Funktion nimmt den pointer auf das Datum und gibt einen String zurück
*/
String Datum_to_String(const tm * datum)
{
  char buffer[100];
  strftime(buffer, 80,  + " %d.%m.%Y  %R:%S Uhr", datum);
  String string = buffer;
  string = wochentag[datum->tm_wday] + string;
  return string;
}
String Datum_to_String(const time_t datum){
  tm x = Datum(datum);
  return Datum_to_String(&x);
}
tm Datum(const time_t unix){
  tm datum;
  localtime_r(&unix, &datum);
  return datum;
}
