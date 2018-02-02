#include <WiFi101.h>

/*
  Simple WebSocket client for ArduinoHttpClient library
  Connects to the WebSocket server, and sends a hello
  message every 5 seconds
  created 28 Jun 2016
  by Sandeep Mistry
  this example is in the public domain
*/
#include <ArduinoArcherPanelClient.h>
#include <WebSocketClient.h>

char ssid[] = "xxx";     //  your network SSID (name)
char pass[] = "xxx";  // your network password

char serverAddress[] = "wsbridge.archer.graphics"; // archer panel websocket endpoint url
int port = 80; // archer panel websocket endpoint port

char panelId[] = "HHCwYhnz"; // the id of the archer panel
char accessKeyId[] = "zBJnIg83"; // the access key id
char accessKey[] = "9e66e504-31a2-4684-bf43-6a03a03f1a33"; // the access key

WiFiClient wifi;
WebSocketClient wsClient(wifi, serverAddress, port);

int status = WL_IDLE_STATUS; 

int count = 0;

bool authenticated = false;

float saturation = 0;
float direction = 1;

void setup() {

  Serial.begin(9600);
  
  while ( status != WL_CONNECTED) {
    
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                  

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
  }

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void connect() {
  
  authenticated = false;

  // open the websocket connection.
  wsClient.begin();

  // create and send authentication command.
  AuthenticateCommand authenticateCommand("zBJnIg83", "9e66e504-31a2-4684-bf43-6a03a03f1a33");
  sendWS(authenticateCommand);
}

/**
 * Send command via websocket to the archer panel
 */
void sendWS(PanelCommand& command) {

  String requestJson = command.toJson();
  wsClient.beginMessage(TYPE_TEXT);
  wsClient.print(requestJson);
  wsClient.endMessage();
  Serial.print("=> ");
  Serial.println(requestJson);
}

/**
 * Read archer panel events from the websocket.
 */
void readWS() {

  if (wsClient.parseMessage() > 0) {
    
    String json = wsClient.readString();
    Serial.print("<= ");
    Serial.println(json);

    // create panel event from received websocket message.
    PanelEvent* event = PanelEvent::jsonToEvent(json);

    // check for AuthenticationResponseEvent
    if(strcmp(event->getType(), AuthenticateResponseEvent::type) == 0) {

      // read authenticated property from event
      authenticated = ((AuthenticateResponseEvent*)event)->isAuthenticated();

      if( authenticated ) {
        
        Serial.println("Authentication successfull!");

        const char* panelIds[1];
        panelIds[0] = "HHCwYhnz";

        // create and send observe panels command. Required for getting events from the panel.
        ObservePanelsCommand observePanelsCommand(panelIds);
        sendWS(observePanelsCommand);
      }
    }
  }
}

void loop() {
  
  if( !wsClient.connected() ) {
    connect();
  } else {
    if( authenticated ) {

      if( saturation >= 1) {
        direction = -1;
      } else if( saturation <= 0) {
        direction = 1;
      }
      saturation += direction*0.02;
      String value(saturation);

      SetVariableCommand setVariableCommand("HHCwYhnz", "saturation", value.c_str(), value.c_str());
      sendWS(setVariableCommand);
    }
  }
  
  readWS();
  delay(200); 
}

