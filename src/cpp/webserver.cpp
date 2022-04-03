#include "header/webserver.h"

AsyncWebServer server(80);

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
    if (var == "TEST_VAR")
    {
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
    if (request->hasParam("input1")) {
      inputMessage = request->getParam("input1")->value();
      inputParam = "input1";
      led_count = inputMessage.toInt();
      strip.clear();
      DEBUG_PRINT("LEDCount: " + String(led_count));
    
    } 
    else if (request->hasParam("input2"))
    {
inputMessage = request->getParam("input2")->value();
      inputMessage = request->getParam("input2")->value();
      inputParam = "input2";
      Scrolling_Text = inputMessage;
      DEBUG_PRINT("Set Scrolling text to: " + inputMessage);
    } else if(request->hasParam("mode")){
inputMessage = request->getParam("mode")->value();
      inputParam = "mode";
      if(inputMessage == "wordclock"){
          DEBUG_PRINT("Set Mode to: " + inputMessage);
          modeWordClock = true;
          modeScrollingText = false;
          modeDigitalClock = false;
      }else if(inputMessage == "digitalclock"){
          DEBUG_PRINT("Set Mode to: " + inputMessage);
          modeWordClock = false;
          modeScrollingText = false;
          modeDigitalClock = true;
      }else if(inputMessage == "scrollingtext"){
          DEBUG_PRINT("Set Mode to: " + inputMessage);
          modeWordClock = false;
          modeScrollingText = true;
          modeDigitalClock = false;
      }
      
    }
    request->send(LittleFS, "/index.html", String(), false, processor); });

    server.on("/led2off", HTTP_GET, [](AsyncWebServerRequest *request)
              {
    led_count = 0;
    strip.clear();
    request->send(LittleFS, "/index.html", String(), false, processor); });

    // Start server
    server.begin();
}