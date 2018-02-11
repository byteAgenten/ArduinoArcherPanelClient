// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

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