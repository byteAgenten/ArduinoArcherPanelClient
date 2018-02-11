// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

#include "ElementClickEvent.h"
#include <Arduino.h>

const char* ElementClickEvent::type = "ELEMENT_CLICK";

ElementClickEvent::ElementClickEvent(
    const char* panelId, 
    const char* elementId) : PanelEvent(),
    iPanelId(panelId), iElementId(elementId) {
   
}

const char* ElementClickEvent::getType() {
    return type;
}

const char* ElementClickEvent::getPanelId() {
    return iPanelId;
}

const char* ElementClickEvent::getElementId() {
    return iElementId;
}
