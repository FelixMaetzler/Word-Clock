#include "header/webserver.h"

AsyncWebServer server(80);
const char *PARAM_INPUT_1 = "input1";

String processor(const String &var)
{
     DEBUG_PRINT(var);
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
        DEBUG_PRINT("LED Strip status: " + ledState);
        return ledState;
    }
    if(var == "TEST_VAR"){
        DEBUG_PRINT("Test: " + String(led_count));
        return String(led_count);
    }
    return String();
}
void webserver_Setup()
{
    if (!LittleFS.begin())
    {
        DEBUG_PRINT("An Error has occurred while mounting LittleFS");
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

    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      led_count = inputMessage.toInt();
      strip.clear();
      DEBUG_PRINT("LEDCount: " + String(led_count));
    request->send(LittleFS, "/index.html", String(), false, processor);
    } });

    // Start server
    server.begin();
}