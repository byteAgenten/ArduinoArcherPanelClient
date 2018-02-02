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