#ifndef COMMS_H
#define COMMS_H

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "config.h"
#include "src/comms/command_dispatcher.h"

class Comms {
private:
    AsyncWebServer server;
    AsyncWebSocket ws;
    AsyncWebSocketMessageHandler wsHandler;
    uint32_t lastWS = 0;
    uint32_t deltaWS = 2000;
    CommandDispatcher &dispatcher;

    void wifi_init();
    void ws_event_handler(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void handle_ws_data(void *arg, uint8_t *data, size_t len);

public:
    Comms(CommandDispatcher &dispatcher):
        server(82), ws("/ws", wsHandler.eventHandler()), dispatcher(dispatcher) {};
    void init();
    void loop();
};

#endif // COMMS_H