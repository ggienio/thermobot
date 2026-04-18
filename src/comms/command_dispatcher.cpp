#include "command_dispatcher.h"
#include <cstring>

void CommandDispatcher::dispatch(JsonDocument &doc) {
    const char *cmd = doc["cmd"];

    if (strcmp(cmd, "MOVE") == 0) {
        const float vx = doc["vx"];
        const float vy = doc["vy"];
        const float omega = doc["omega"];
        movement.move(vx, vy, omega);
    }
}