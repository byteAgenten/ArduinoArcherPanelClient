#ifndef AuthenticateResponseEvent_H
#define AuthenticateResponseEvent_H

#include "PanelEvent.h"

class AuthenticateResponseEvent : public PanelEvent {


    public:
        AuthenticateResponseEvent(bool authenticated);
        static const char* type;
        bool isAuthenticated();
        virtual const char* getType();
    private:
        bool iAuthenticated;
};

#endif