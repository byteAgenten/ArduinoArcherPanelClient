// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

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