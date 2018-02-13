// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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