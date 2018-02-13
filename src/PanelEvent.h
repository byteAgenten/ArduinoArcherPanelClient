// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

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