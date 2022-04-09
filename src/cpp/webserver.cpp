#include "header/webserver.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
bool test1234 = false;
void notifyClients()
{
    constexpr uint8_t size = JSON_OBJECT_SIZE(json_elements_count);
    StaticJsonDocument<size> json;
    json["status"] = test1234 ? "on" : "off";

    char data[17];
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

        constexpr uint8_t size = JSON_OBJECT_SIZE(json_elements_count);
        StaticJsonDocument<size> json;
        DeserializationError err = deserializeJson(json, data);
        if (err)
        {
            Serial.print(F("deserializeJson() failed with code "));
            Serial.println(err.c_str());
            return;
        }
        const char *action = json["action"];
        if (strcmp(action, "toggle") == 0)
        {
            test1234 = !test1234;
            notifyClients();
        }
    }
}
