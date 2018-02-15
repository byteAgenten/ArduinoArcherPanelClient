// Copyright (c) 2018 byteAgenten gmbh, germany. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

//This example is a very basic simulation of an elevator control logic
//To use this example you need to register (for free) to the Archer Cloud at https://cloud.archer.graphics/host
//Please read our Archer Cloud documentation to understand the Archer Cloud
//concepts at https://wiki.archer.graphics/display/ARCHER/Archer+Cloud
//You can download the used archer.graphics project from http://archer.graphics/submenu/resources/

#include <WiFi101.h>
#include <WebSocketClient.h>
#include <ArduinoArcherPanelClient.h>

struct Floor {
    char *buttonElementId; //The ID of the associated floor selection button element inside the panel SVG
    int interruptPin;   //The associated interrupt pin on the arduino board
    int ledPin; //The associated led output pin on the arduino board
    boolean selected;   //The selection status of the associated floor
};

const int FLOOR_COUNT = 6;
const int DOOR_OPEN_TIME = 2; // 2 seconds
const float FLOOR_HEIGHT = 3; // 3 meter
const float ELEVATOR_SPEED = 2; // 2 meter/seconds

Floor floors[FLOOR_COUNT];

const char PANEL_ID[] = "******"; //replace with your Archer Cloud panel id
const char ACCESS_KEY_ID[] = "******"; //replace with your Archer Cloud access key id
const char ACCESS_KEY[] = "********-****-****-****-************"; //replace with your Archer Cloud acccess key

const char SSID[] = "*********"; //replace with your WLAN name
const char WAP[] = "***************"; //replace with your WLAN password

const char WS_URL[] = "wsbridge.archer.graphics";   //url to the Archer Cloud panel websocket endpoint
const int WS_PORT = 80; //port of the websocket endpoint


boolean moveUp = true;  //indicates the direction of the elevator
int nextFloorIndex = 0;
int lastFloorIndex = 0;
int currentFloorIndex = 0;
boolean moving = false; //indicates that the elevator is moving
bool isAuthenticated = false;   //the status of the Archer panel authentication
long lastMillis = 0;    //stores the time from the previous loop() execution.
float lastHeight = 0;   //stores the last height position of the elevator from the previous loop() execution.
float currentHeight = 0;    //the current height position of the elevator
long doorOpenStartMillis;   //stores the time when the elevator doors started to open

//Create the wifi client
WiFiClient wifi;

//Create the websocket client
WebSocketClient wsClient(wifi, WS_URL, WS_PORT);

int wifiStatus = WL_IDLE_STATUS;    //stores the current wifi connection status


void setup() {

    Serial.begin(9600);

    while (wifiStatus != WL_CONNECTED) {

        Serial.print("Attempting to connect to Network named: ");
        Serial.println(SSID);

        // Connect to the WLAN
        wifiStatus = WiFi.begin(SSID, WAP);
    }
    Serial.print("Network connected successfully!");

    //initiate temp variables
    lastMillis = millis();
    lastHeight = lastFloorIndex * FLOOR_HEIGHT;

    //initiate floor definitions
    floors[0] = {(char *) "b-1", 1, 0, false};
    floors[1] = {(char *) "b0", 4, 2, false};
    floors[2] = {(char *) "b1", 5, 3, false};
    floors[3] = {(char *) "b2", 6, 9, false};
    floors[4] = {(char *) "b3", 7, 10, false};
    floors[5] = {(char *) "b4", 8, 11, false};

    //initiate pins on arduino board
    for (int i = 0; i < FLOOR_COUNT; i++) {

        pinMode(floors[i].ledPin, OUTPUT);
        digitalWrite(floors[i].ledPin, LOW);
        pinMode(floors[i].interruptPin, INPUT_PULLUP);
    }

    //attach each floor selection button to an interrupt pin
    attachInterrupt(digitalPinToInterrupt(floors[0].interruptPin), floor0, RISING);
    attachInterrupt(digitalPinToInterrupt(floors[1].interruptPin), floor1, RISING);
    attachInterrupt(digitalPinToInterrupt(floors[2].interruptPin), floor2, RISING);
    attachInterrupt(digitalPinToInterrupt(floors[3].interruptPin), floor3, RISING);
    attachInterrupt(digitalPinToInterrupt(floors[4].interruptPin), floor4, RISING);
    attachInterrupt(digitalPinToInterrupt(floors[5].interruptPin), floor5, RISING);

    //Connect to the Archer Cloud
    connectArcherCloud();
}

void loop() {

    //Calculate elapsed time (seconds) since previous loop() execution
    int currentMillis = millis();
    float deltaSeconds = ((float) currentMillis - (float) lastMillis) / 1000.0;

    //Check if the cabin is currently moving
    if (moving) {

        //Calculate the moved distance (meter) since the last loop() execution
        float distanceMoved = deltaSeconds * ELEVATOR_SPEED;

        //Calculate the current height position of the cabin
        currentHeight = lastHeight + (moveUp ? 1 : -1) * distanceMoved;

        //Check whether the next selected floor is reached
        if (hasNextSelectedFloorReached()) {

            //Handle floor reached
            floorReached(nextFloorIndex);

        } else {

            //Calculate the floor which the cabin is currently passing
            int floorIndex = round(currentHeight / FLOOR_HEIGHT);

            //If the floor is different to the floor at the last loop() execution
            if (floorIndex != currentFloorIndex) {

                //Update the current floor to the new floor index
                currentFloorIndex = floorIndex;

                //Send the current floor index as value of the 'curfloor' variable to the Archer panel.
                String currentFloorValue(floorIndex - 1);
                SetVariableCommand setVariableCommand(PANEL_ID, "curfloor", currentFloorValue.c_str(),
                                                      currentFloorValue.c_str());
                sendWS(setVariableCommand);
            }
        }

        //update the cabin position
        updateCabPos();

        //store the current height for the next loop() execution
        lastHeight = currentHeight;

    } else {


        if (millis() < doorOpenStartMillis + DOOR_OPEN_TIME * 1000) {

            //Do nothing, just wait 2 seconds

        } else {

            //Check for another selected floor and start moving if there is one.
            if (!moving) {
                nextFloorIndex = getNextSelectedFloor();
                setMoving(nextFloorIndex >= 0);
            }

        }

    }

    //store the current millis for the use in the next loop() execution
    lastMillis = currentMillis;

    //Check for available events from the Archer panel
    readWS();

    //Wait for 200ms
    delay(200);
}


/**
 * Callback function(s) for the interrupt pin(s)
 */
void floor0() { selectFloor(0); }

void floor1() { selectFloor(1); }

void floor2() { selectFloor(2); }

void floor3() { selectFloor(3); }

void floor4() { selectFloor(4); }

void floor5() { selectFloor(5); }

/**
 * Opens the websocket connection and sends an authentication request
 */
void connectArcherCloud() {

    isAuthenticated = false;

    //open websocket connection
    wsClient.begin();

    //create and send an authentication request.
    AuthenticateCommand authenticateCommand(ACCESS_KEY_ID, ACCESS_KEY);
    sendWS(authenticateCommand);
}

/**
 * Generic function for sending commands via websocket to the Archer Cloud
 */
void sendWS(PanelCommand &command) {

    String requestJson = command.toJson();
    wsClient.beginMessage(TYPE_TEXT);
    wsClient.print(requestJson);
    wsClient.endMessage();
}

/**
 * Generic function for reading Archer panel events from the websocket
 */
void readWS() {

    //check if data available at the websocket
    if (wsClient.parseMessage() > 0) {

        //read the data from the websocket. Data send from Archer Cloud are in JSON format.
        String json = wsClient.readString();

        //create a panel event instance from the received websocket message.
        PanelEvent *event = PanelEvent::jsonToEvent(json);

        handlePanelEvent(event);
    }
}

/**
 * Handles received panel events
 */
void handlePanelEvent(PanelEvent *event) {

    //Determine the type of the panel event.
    if (event->isTypeOf(AuthenticateResponseEvent::type)) {

        handleAuthenticationEvent((AuthenticateResponseEvent *) event);

    } else if (event->isTypeOf(ElementClickEvent::type)) {

        handleElementClickEvent((ElementClickEvent *) event);
    }
}

/**
 * Handle the response from a previously sent authentication request
 */
void handleAuthenticationEvent(AuthenticateResponseEvent *event) {


    //Check if the authentication was successful
    if (event->isAuthenticated()) {

        Serial.println("Authentication successful!");

        //Create an char array for storing all panelIds from which you want to get events.
        //In this case we are interested only in events from one panel.
        const char *panelIds[1];
        panelIds[0] = PANEL_ID;

        //Create and send ObservePanelsCommand.
        ObservePanelsCommand observePanelsCommand(panelIds);
        sendWS(observePanelsCommand);

        //Initialize the panel variables.
        for (int i = 0; i < FLOOR_COUNT; i++) {
            setButtonState(i, (char *) "default");
        }

        updateCabPos();
    }
}

/**
 * Handles the click events received from the panel.
 */
void handleElementClickEvent(ElementClickEvent *event) {

    //Determine the element that was clicked at the panel
    String elementId = event->getElementId();

    //Find the associated floor
    for (int i = 0; i < FLOOR_COUNT; i++) {
        if (strcmp(elementId.c_str(), floors[i].buttonElementId) == 0) {

            //Select the floor
            selectFloor(i);
        }
    }
}





/**
 * Checks whether the next selected floor is reached.
 */
boolean hasNextSelectedFloorReached() {

    float nextFloorHeight = nextFloorIndex * FLOOR_HEIGHT;

    if (moveUp && currentHeight >= nextFloorHeight) {

        return true;

    } else if (!moveUp && currentHeight <= nextFloorHeight) {

        return true;
    }
    return false;
}

/**
 * Sets the move direction.
 */
void setMoveUp(boolean value) {

    if (value == moveUp) return;

    moveUp = value;

    //Build the panel variable value
    String movementValue(moveUp ? "up" : "down");

    //Send the new value for the 'movement' variable to the Archer panel.
    SetVariableCommand setVariableCommand(PANEL_ID, "movement", movementValue.c_str(), movementValue.c_str());
    sendWS(setVariableCommand);
}

/**
 * Sets the move state.
 */
void setMoving(boolean value) {

    if (value == moving) return;
    moving = value;
    if (moving) {
        setButtonState(lastFloorIndex, (char *) "default");
    }
}

/**
 * Finds the next selected floor depending on the position and move direction of the cabin position.
 * Returns the index of the floor or -1, if none is selected.
 */
int getNextSelectedFloor() {

    int nextSelectedFloor = -1;

    if (moveUp) {

        nextSelectedFloor = nextSelectedUpperFloor();
        if (nextSelectedFloor < 0) {

            nextSelectedFloor = nextSelectedLowerFloor();
            if (nextSelectedFloor >= 0) {
                setMoveUp(false);
            }
        }

    } else {

        nextSelectedFloor = nextSelectedLowerFloor();
        if (nextSelectedFloor < 0) {

            nextSelectedFloor = nextSelectedUpperFloor();
            if (nextSelectedFloor >= 0) {
                setMoveUp(true);
            }
        }
    }
    return nextSelectedFloor;
}

/**
 * Checks whether a floor above to the current cabin position is selected.
 * Returns the index of the floor or -1, if none is selected.
 */
int nextSelectedUpperFloor() {

    for (int floorIndex = lastFloorIndex; floorIndex < FLOOR_COUNT; floorIndex++) {

        if (floors[floorIndex].selected) {
            return floorIndex;
        }
    }
    return -1;
}

/**
 * Checks whether a floor below to the current cabin position is selected.
 * Returns the index of the floor or -1, if none is selected.
 */
int nextSelectedLowerFloor() {

    for (int floorIndex = lastFloorIndex; floorIndex >= 0; floorIndex--) {

        if (floors[floorIndex].selected) {
            return floorIndex;
        }
    }
    return -1;
}

/**
 * Updates the cabin position.
 */
void updateCabPos() {

    //Calculate the variable value for the panel
    String cabinPosValue(currentHeight / ((FLOOR_COUNT - 1) * FLOOR_HEIGHT) * 500);

    //Send the calculated value for the 'cabpos' variable to the Archer panel.
    SetVariableCommand setVariableCommand(PANEL_ID, "cabpos", cabinPosValue.c_str(), cabinPosValue.c_str());
    sendWS(setVariableCommand);
}

/**
 * Executes all necessary things when a floor is reached by the cabin.
 */
void floorReached(int floorIndex) {

    //stop cabin from moving
    setMoving(false);

    //clear the selected state of the reached floor
    floors[nextFloorIndex].selected = false;

    //store the start time of doors opening.
    doorOpenStartMillis = millis();

    //calculate the height position of the cabin
    currentHeight = nextFloorIndex * FLOOR_HEIGHT;

    //store the current floor index
    lastFloorIndex = nextFloorIndex;

    //switch off the floor led
    digitalWrite(floors[lastFloorIndex].ledPin, LOW);

    //Update the button state of the reached floor to 'current' within the Archer panel graphic
    setButtonState(floorIndex, (char *) "current");
}


/**
 * Sets a floor to the 'selected' state.
 */
void selectFloor(int floorIndex) {

    if (floors[floorIndex].selected) return;

    //Set the associated pin to HIGH
    floors[floorIndex].selected = true;
    digitalWrite(floors[floorIndex].ledPin, HIGH);

    //Update the button state to 'selected' within the Archer panel graphic
    setButtonState(floorIndex, (char *) "selected");
}

/**
 * Sets the state of an button.
 */
void setButtonState(int floorIndex, char *state) {

    //Build the associated panel variable name
    String variable = String("button-state-");
    variable.concat(floorIndex);

    //Send the state value for the associated variable to the Archer panel.
    SetVariableCommand setVariableCommand(PANEL_ID, variable.c_str(), state, state);
    sendWS(setVariableCommand);
}
