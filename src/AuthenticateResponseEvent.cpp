// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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