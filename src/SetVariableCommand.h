// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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
