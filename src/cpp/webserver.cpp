#include "header/webserver.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
bool test1234 = false;
void notifyClients()
{
    constexpr uint16_t size = JSON_OBJECT_SIZE(json_elements_count);
    StaticJsonDocument<size> json;
    json["status"] = test1234 ? "on" : "off";
    json["scrollingText"] = Scrolling_Text;
    json["modeDC"] = modeDigitalClock;
    json["modeWC"] = modeWordClock;
    json["modeST"] = modeScrollingText;
    json["R"] = color.get_r();
    json["G"] = color.get_g();
    json["B"] = color.get_b();

    char data[170];
    size_t len = serializeJson(json, data);
    DEBUG_PRINT("JSON: " + String(data));
    ws.textAll(data, len);
}

String processor(const String &var)
{
    return String();
}
void onEvent(AsyncWebSocket *server,
             AsyncWebSocketClient *client,
             AwsEventType type,
             void *arg,
             uint8_t *data,
             size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:

        DEBUG_PRINT("WebSocket client #" + String(client->id()) + " connected from " + String(client->remoteIP().toString().c_str()) + "\n");
        break;
    case WS_EVT_DISCONNECT:
        DEBUG_PRINT("WebSocket client #" + String(client->id()) + " disconnected\n");
        break;
    case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}
void websocket_Setup()
{
    DEBUG_PRINT("test2");
    ws.onEvent(onEvent);
    server.addHandler(&ws);
}
void onRootRequest(AsyncWebServerRequest *request)
{
    request->send(LittleFS, "/index.html", "text/html", false, processor);
}
void webserver_Setup()
{
    if (!LittleFS.begin())
    {
        DEBUG_PRINT("An Error has occurred while mounting LittleFS");
        return;
    }
    if (MDNS.begin("wordclock"))
    {
        DEBUG_PRINT("MDNS started");
    }
    server.on("/", onRootRequest);
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

    // Start server
    server.begin();
}
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {

        constexpr uint16_t size = JSON_OBJECT_SIZE(json_elements_count);
        StaticJsonDocument<size> json;
        DeserializationError err = deserializeJson(json, data);
        if (err)
        {
            Serial.print(F("deserializeJson() failed with code ")); // To do
            Serial.println(err.c_str());                            // To do
            return;
        }
        // TO DO...
        // const char *action = json["action"];
        // const char *scrollingText = json["scrollingText"];
        Scrolling_Text = (String)json["scrollingText"];
        modeDigitalClock = ((String)json["modeDC"]).toInt();
        modeScrollingText = ((String)json["modeST"]).toInt();
        modeWordClock = ((String)json["modeWC"]).toInt();
        color = RGB(((String)json["R"]).toInt(), ((String)json["G"]).toInt(), ((String)json["B"]).toInt());
        notifyClients();
    }
}
