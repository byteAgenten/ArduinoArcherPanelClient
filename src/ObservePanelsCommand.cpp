// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

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