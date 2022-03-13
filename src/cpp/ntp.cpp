#include "header/release.h"
#include "header/secret.h"
#include "header/ntp.h"

#include <TZ.h>

// Kümmert sich um die Zeitumstellung. Winter- Sommerzeit
#define MYTZ TZ_Europe_Berlin
// Die "deutschen" Wochentage abgekürzt. Beginnend mit Sonntag
// Wird für das serielle Debuggen benötigt
const char *wochentag[] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa"};

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
Diese Funktion nimmt den Pointer auf das Datum und gibt einen String zurück
Beispiel:
So 13.03.2022 09:34:00 Uhr
*/
String Datum_to_String(const tm *datum)
{
  char buffer[100];
  strftime(buffer, 80, +" %d.%m.%Y  %R:%S Uhr", datum);
  String string = buffer;
  string = wochentag[datum->tm_wday] + string;
  return string;
}
/*
Konvertiert ein Datum in einen String
Beispiel:
So 13.03.2022 09:34:00 Uhr
*/
String Datum_to_String(const time_t datum)
{
  tm x = Datum(datum);
  return Datum_to_String(&x);
}
/*
konvertiert die Unix-Zeit in ein richtiges Datum
Sommer und Winterzeit ist schon berücksichtigt
*/
tm Datum(const time_t unix)
{
  tm datum;
  localtime_r(&unix, &datum);
  return datum;
}
/*
Synchronisiert die interne Zeit mit dem Internet falls dieses verfügbar ist
Wenn nicht, dann bleibt die alte einfach weiter bestehen
gibt zurück, ob Sync erfolgreich war oder eben nicht
ACHTUNG!!! Diese Funktion kann mehr als 5 sek brauchen!!!
*/
bool syncDatum(volatile time_t *ptr)
{
  time_t datum;
  int counter = 0;
  /*
  Versucht die Zeit zu synchronisieren
  Entweder bis die Abweichung kleiner als 10 sek ist oder bis er es 5 Mal versucht hat
  */
  do
  {
    datum = get_Datum();

    counter++;
    noInterrupts();
    int akt = *ptr;
    interrupts();
    int diff = abs(datum - akt);
    if (diff < 10)
    {
      noInterrupts();
      *ptr = datum;
      interrupts();
      DEBUG_PRINT("Sync hat nach " + String(counter) + " Versuchen geklappt\nOffset waren: " + String(diff) + "s");
      return true;
    }
    delay(1000);
  } while (counter < 5);
  return false;
}