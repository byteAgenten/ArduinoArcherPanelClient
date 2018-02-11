// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

#include "KeepAliveCommand.h"
#include <Arduino.h>

const char* KeepAliveCommand::type = "KEEP_ALIVE";

KeepAliveCommand::KeepAliveCommand() : PanelCommand() {
   
}

String KeepAliveCommand::toJson() {

    const char* requestValues[1];
    requestValues[0] = type;
    String json = PanelCommand::arrayToJson(requestValues, 1);
    
    return json; 
}