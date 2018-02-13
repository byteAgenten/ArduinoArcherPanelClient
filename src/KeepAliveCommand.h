// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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