// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

#ifndef ElementClickEvent_H
#define ElementClickEvent_H

#include "PanelEvent.h"

class ElementClickEvent : public PanelEvent {


    public:
        ElementClickEvent(const char* panelId, const char* elementId);
        static const char* type;
        virtual const char* getType();
        const char* getPanelId();
        const char* getElementId();
    private:
        const char* iPanelId;
        const char* iElementId;
};

#endif