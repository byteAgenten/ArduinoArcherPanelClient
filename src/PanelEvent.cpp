// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PanelEvent.h"
#include "AuthenticateResponseEvent.h"
#include "UserValueInputEvent.h"
#include "ElementClickEvent.h"
#include <Arduino.h>


PanelEvent::PanelEvent() {
   
}

bool PanelEvent::isTypeOf(const char* type) {

    return strcmp(this->getType(), type) == 0;
}

void PanelEvent::writeJsonTokensToArray(String json, const char** eventTokens) {

    int tokenCount = 0;
    
    bool stringStarted = false;

    String currentString;

    int l = json.length();
   
    for( int i=0; i < l; i++) {
        char c = json.charAt(i);
        
        if( c == '\"') {
            if( !stringStarted) {
                stringStarted = true;
                currentString = "";
            } else {
                char* cpy = new char[currentString.length()];
                strcpy(cpy, currentString.c_str());
                eventTokens[tokenCount++] = cpy;
                stringStarted = false;
            }
        } else {

            if( stringStarted) {
                currentString += c;
            }
        }
    }
}

PanelEvent* PanelEvent::jsonToEvent(String json) {

    const char* eventTokens[20];

    PanelEvent* event;

    PanelEvent::writeJsonTokensToArray(json, eventTokens);

    const char* eventType = eventTokens[0];
    
    if(strcmp(eventType, AuthenticateResponseEvent::type) == 0) {

            AuthenticateResponseEvent* authenticateResponse = new AuthenticateResponseEvent(strcmp(eventTokens[2],"OK")==0);
            event = authenticateResponse;
    
    } else if(strcmp(eventType, UserValueInputEvent::type) == 0) {

        UserValueInputEvent* userValueInputEvent = new UserValueInputEvent(
            eventTokens[1],
            eventTokens[3],
            eventTokens[4],
            eventTokens[5]);
        event = userValueInputEvent;

    } else if(strcmp(eventType, ElementClickEvent::type) == 0) {

        ElementClickEvent* elementClickEvent = new ElementClickEvent(
            eventTokens[1],
            eventTokens[2]);
        event = elementClickEvent;
    } 
    return event;
    

    
}