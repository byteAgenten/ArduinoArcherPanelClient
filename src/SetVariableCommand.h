#ifndef SetVariableCommand_H
#define SetVariableCommand_H

#include "PanelCommand.h"

class SetVariableCommand : public PanelCommand {


    public:
        SetVariableCommand(const char* iPanelId, const char* iVariableKey, const char* iVariableValue, const char* iVariableDisplayValue);
        virtual String toJson();
        const char* type = "VARIABLE_CHANGED";
    private:
        const char* iPanelId;
        const char* iVariableKey;
        const char* iVariableValue;
        const char* iVariableDisplayValue;
        
};

#endif
