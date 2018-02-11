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