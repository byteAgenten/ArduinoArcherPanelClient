#ifndef KeepAliveCommand_H
#define KeepAliveCommand_H

#include "PanelCommand.h"

class KeepAliveCommand : public PanelCommand {


    public:
        KeepAliveCommand();
        virtual String toJson();
        static const char* type;
    private:
        
};

#endif