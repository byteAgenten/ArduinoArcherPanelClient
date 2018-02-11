// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

#include "UserValueInputEvent.h"
#include <Arduino.h>

const char* UserValueInputEvent::type = "USER_VALUE_INPUT";

UserValueInputEvent::UserValueInputEvent(
    const char* panelId, 
    const char* inputKey,
    const char* oldValue, 
    const char* newValue) : PanelEvent(),
    iPanelId(panelId), iInputKey(inputKey), iOldValue(oldValue), iNewValue(newValue) {
   
}

const char* UserValueInputEvent::getType() {
    return type;
}

const char* UserValueInputEvent::getPanelId() {
    return iPanelId;
}

const char* UserValueInputEvent::getInputKey() {
    return iInputKey;
}

const char* UserValueInputEvent::getOldValue() {
    return iOldValue;
}

const char* UserValueInputEvent::getNewValue() {
    return iNewValue;
}


