// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

#include "AuthenticateResponseEvent.h"
#include <Arduino.h>

const char* AuthenticateResponseEvent::type = "AUTHENTICATE_RESPONSE";

AuthenticateResponseEvent::AuthenticateResponseEvent(bool authenticated) : PanelEvent(), iAuthenticated(authenticated) {
   
}

const char* AuthenticateResponseEvent::getType() {
    return type;
}

bool AuthenticateResponseEvent::isAuthenticated() {
    return iAuthenticated;
}