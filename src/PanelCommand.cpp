// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PanelCommand.h"
#include <Arduino.h>


PanelCommand::PanelCommand() {
   
}

String PanelCommand::arrayToJson(const char* values[], int length) {


    String json = "[";
    for( int i=0; i < length; i++) {

        String s1 = String("\"");
        String s2 = String(values[i]);
        String s3 = String("\"");

        s1.concat(s2);
        s1.concat(s3);

        if( i > 0) json += ",";
        json += s1;
    }
    json.concat("]");
    return json;
}