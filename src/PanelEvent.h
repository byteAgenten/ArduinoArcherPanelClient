// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

#ifndef PanelEvent_H
#define PanelEvent_H

#include <Arduino.h>


class PanelEvent {


    public:
        PanelEvent();
        static PanelEvent* jsonToEvent(String json);
        virtual const char* getType()=0;
        bool isTypeOf(const char* type);

    private:
         static void writeJsonTokensToArray(String json, const char** eventTokens);
        
};

#endif