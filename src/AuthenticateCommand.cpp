// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "AuthenticateCommand.h"
#include <Arduino.h>

const char *AuthenticateCommand::type = "AUTHENTICATE_REQUEST";

AuthenticateCommand::AuthenticateCommand(const char *accessKeyId, const char *accessKey)
        : PanelCommand(), iAccessKeyId(accessKeyId), iAccessKey(accessKey) {

}


String AuthenticateCommand::toJson() {

    const char *requestValues[5];
    requestValues[0] = type;
    requestValues[1] = "1";
    requestValues[2] = iAccessKeyId;
    requestValues[3] = iAccessKey;
    requestValues[4] = "Client";
    String json = PanelCommand::arrayToJson(requestValues, 5);
    //Serial.println(json);

    return json;
}