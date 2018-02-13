// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef ObservePanelsCommand_H
#define ObservePanelsCommand_H

#include "PanelCommand.h"

class ObservePanelsCommand : public PanelCommand {


    public:
        ObservePanelsCommand(const char** panelIds);
        virtual String toJson();
        static const char* type;
    private:
        const char** iPanelIds;
        
};

#endif