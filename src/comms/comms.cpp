#include "comms.h"

static const char *htmlContent PROGMEM = R"(
<!DOCTYPE html>
<html>
<head>
    <title>WebSocket</title>
</head>
<body>
    <h1>WebSocket Example</h1>
    <p>Open your browser console!</p>
    <input type="text" id="message" placeholder="Type a message">
    <button onclick='sendMessage()'>Send</button>
    <script>
        var ws = new WebSocket('ws://192.168.4.1/ws');
        ws.onopen = function() {
            console.log("WebSocket connected");
        };
        ws.onmessage = function(event) {
            console.log("WebSocket message: " + event.data);
        };
        ws.onclose = function() {
            console.log("WebSocket closed");
        };
        ws.onerror = function(error) {
            console.log("WebSocket error: " + error);
        };
        function sendMessage() {
            var message = document.getElementById("message").value;
            ws.send(message);
            console.log("WebSocket sent: " + message);
        }
    </script>
</body>
</html>
)";
static const size_t htmlContentLength = strlen_P(htmlContent);

void Comms::init() {
    // if(!SPIFFS.begin()) {
    //     Serial.println("Error mounting SPIFFS");
    //     while(1);
    // }
    wifi_init();

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/html", (const uint8_t *)htmlContent, htmlContentLength);
    });

    ws.onEvent(Comms::ws_event_handler);
    server.addHandler(&ws);
    server.begin();
};

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
            Comms::handle_ws_data(arg, data, len);
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
    }
}