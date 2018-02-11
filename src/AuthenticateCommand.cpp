// Library to connect to archer.graphics panel
// (c) Copyright byteAgenten gmbh. 2018
// Released under Apache License, version 2.0

#include "AuthenticateCommand.h"
#include <Arduino.h>

const char* AuthenticateCommand::type = "AUTHENTICATE_REQUEST";

AuthenticateCommand::AuthenticateCommand(const char* accessKeyId, const char* accessKey) : PanelCommand(), iAccessKeyId(accessKeyId), iAccessKey(accessKey) {
   
}


String AuthenticateCommand::toJson() {

    const char* requestValues[5];
    requestValues[0] = type;
    requestValues[1] = "1";
    requestValues[2] = iAccessKeyId;
    requestValues[3] = iAccessKey;
    requestValues[4] = "Client";
    String json = PanelCommand::arrayToJson(requestValues, 5);
    //Serial.println(json);

    return json; 
}