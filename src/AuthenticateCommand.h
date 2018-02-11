// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

#ifndef AuthenticateCommand_H
#define AuthenticateCommand_H

#include "PanelCommand.h"

class AuthenticateCommand : public PanelCommand {


    public:
        AuthenticateCommand(const char* accessKeyId, const char* accessKey);
        virtual String toJson();
        static const char* type;
    private:
        const char* iAccessKeyId;
        const char* iAccessKey;
        
        
};

#endif