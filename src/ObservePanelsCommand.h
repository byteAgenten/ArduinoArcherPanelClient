// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

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