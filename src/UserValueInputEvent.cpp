// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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


