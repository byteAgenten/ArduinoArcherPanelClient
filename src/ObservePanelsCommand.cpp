// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "ObservePanelsCommand.h"
#include <Arduino.h>

const char* ObservePanelsCommand::type = "OBSERVE_PANELS_REQUEST";

ObservePanelsCommand::ObservePanelsCommand(const char** panelIds) : PanelCommand(), iPanelIds(panelIds) {
   
}

String ObservePanelsCommand::toJson() {

    int length = sizeof(iPanelIds)/sizeof(char*);
    
    const char* requestValues[length+2];
    requestValues[0] = type;
    requestValues[1] = "1";
    for( int i=0; i < length; i++) {
        requestValues[i+2] = iPanelIds[i];
    }
    String json = PanelCommand::arrayToJson(requestValues, length+2);
    
    return json; 
}