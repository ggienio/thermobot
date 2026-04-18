#ifndef COMMAND_DISPATCHER_H
#define COMMAND_DISPATCHER_H

#include "src/control/movement.h"
#include <ArduinoJson.h>

class CommandDispatcher {
public:
    CommandDispatcher(Movement &movement): movement(movement) {};
    
    void dispatch(JsonDocument &doc);
    
private:
    Movement& movement;
};

#endif // COMMAND_DISPATCHER_H