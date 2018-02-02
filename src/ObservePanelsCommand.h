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