// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef PanelCommand_H
#define PanelCommand_H

#include <Arduino.h>

class PanelCommand {

    public:
        PanelCommand();
        virtual String toJson() = 0;
        
    protected:
        static String arrayToJson(const char* values[], int length);

    private:
        
};

#endif