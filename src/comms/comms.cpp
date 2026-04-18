#include "comms.h"
#include <ArduinoJson.h>

void Comms::init() {
    wifi_init();

    ws.onEvent([this] (AsyncWebSocket *server, AsyncWebSocketClient *client,
                       AwsEventType type, void *arg, uint8_t *data, size_t len) {
        this->ws_event_handler(server, client, type, arg, data, len);
    });
    server.addHandler(&ws);
    server.begin();
}

void Comms::loop() {
    uint32_t now = millis();

    if (now - lastWS >= deltaWS) {
        ws.cleanupClients();
        ws.printfAll("now: %" PRIu32 "\n", now);
        lastWS = millis();
    }
}

void Comms::wifi_init() {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(WiFiConf::AP_SSID, WiFiConf::AP_PASSWORD);

    Serial.println("AP running");
    Serial.print("My IP address: ");
    Serial.println(WiFi.softAPIP());
}

void Comms::ws_event_handler(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
        case WS_EVT_CONNECT:
            Serial.printf("WebSocket client #%u connected from %s\n", (uint16_t)client->id(), client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            Serial.printf("WebSocket client #%u disconnected\n", (uint16_t)client->id());
            break;
        case WS_EVT_DATA:
            handle_ws_data(arg, data, len);
            break;
        case WS_EVT_PING:
        case WS_EVT_PONG:
        case WS_EVT_ERROR:
            break;
    }
}

void Comms::handle_ws_data(void *arg, uint8_t *data, size_t len) {
    AwsFrameInfo *info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        data[len] = 0;
        Serial.printf("WebSocket data received: %s\n", (const char *)data);
        JsonDocument doc;
        deserializeJson(doc, (const char *)data);
        dispatcher.dispatch(doc);
    }
}