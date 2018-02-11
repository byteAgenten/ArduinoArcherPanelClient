// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

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