// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

#ifndef SetVariableCommand_H
#define SetVariableCommand_H

#include "PanelCommand.h"

class SetVariableCommand : public PanelCommand {

    public:
        SetVariableCommand(const char* iPanelId, const char* iVariableKey, const char* iVariableValue, const char* iVariableDisplayValue);
        virtual String toJson();
        static const char* type;
    private:
        const char* iPanelId;
        const char* iVariableKey;
        const char* iVariableValue;
        const char* iVariableDisplayValue;
        
};

#endif
