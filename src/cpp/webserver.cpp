#include "header/webserver.h"

AsyncWebServer server(80);

String processor(const String &var)
{
    Serial.println(var);
    if (var == "GPIO_STATE")
    {
        if (!led_count)
        {
            ledState = "OFF";
        }
        else
        {
            ledState = "ON";
        }
        Serial.print(ledState);
        return ledState;
    }
    return String();
}
void webserver_Setup()
{
    if (!LittleFS.begin())
    {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", String(), false, processor); });

    // Route to load style.css file
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/style.css", "text/css"); });

    // Route to set GPIO to HIGH
    server.on("/led2on", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    led_count = 15;   
    request->send(LittleFS, "/index.html", String(), false, processor); });

    // Route to set GPIO to LOW
    server.on("/led2off", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    led_count = 0;
    strip.clear();
    request->send(LittleFS, "/index.html", String(), false, processor); });

    // Start server
    server.begin();
}