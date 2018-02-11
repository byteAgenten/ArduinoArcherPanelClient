// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

#ifndef UserValueInputEvent_H
#define UserValueInputEvent_H

#include "PanelEvent.h"

class UserValueInputEvent : public PanelEvent {


    public:
        UserValueInputEvent(const char* panelId, const char* inputKey, const char* oldValue, const char* newValue);
        static const char* type;
        virtual const char* getType();
        const char* getPanelId();
        const char* getInputKey();
        const char* getOldValue();
        const char* getNewValue();
    private:
        const char* iPanelId;
        const char* iInputKey;
        const char* iOldValue;
        const char* iNewValue;
};

#endif