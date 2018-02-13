// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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