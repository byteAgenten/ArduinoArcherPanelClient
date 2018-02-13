// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "SetVariableCommand.h"
#include <Arduino.h>

const char* SetVariableCommand::type = "VARIABLE_CHANGED";
        
SetVariableCommand::SetVariableCommand(const char* panelId, const char* variableKey, const char* variableValue, const char* variableDisplayValue) : PanelCommand(), iPanelId(panelId), iVariableKey(variableKey), iVariableValue(variableValue), iVariableDisplayValue(variableDisplayValue)  {
   
}


String SetVariableCommand::toJson() {

    const char* commandValues[5];
    commandValues[0] = type;
    commandValues[1] = iPanelId;
    commandValues[2] = iVariableKey;
    commandValues[3] = iVariableValue;
    commandValues[4] = iVariableDisplayValue;
    String commandJson = PanelCommand::arrayToJson(commandValues, 5);
    //Serial.println(json);

    return commandJson; 
}