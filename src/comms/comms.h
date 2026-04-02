#ifndef COMMS_H
#define COMMS_H

#include <WiFi.h>
//#include <SPIFFS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "config.h"

class Comms {
private:
    AsyncWebServer server;
    AsyncWebSocket ws;
    AsyncWebSocketMessageHandler wsHandler;
    uint32_t lastWS = 0;
    uint32_t deltaWS = 2000;

    void wifi_init();
    static void ws_event_handler(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    static void handle_ws_data(void *arg, uint8_t *data, size_t len);

public:
    Comms() : server(80), ws("/ws", wsHandler.eventHandler()) {};
    void init();
    void loop();
};

#endif // COMMS_H