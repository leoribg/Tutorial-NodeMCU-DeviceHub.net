/*
 *  Simple HTTP get webclient test - By Leonardo Gonçalves - Instituto Nacional de Telecomunicações INATEL - Brazil
 */
#include <ESP8266WiFi.h>
const char* ssid     = "SSID";
const char* password = "PASSWORD";
String pubString;
const char* host = "api.devicehub.net";//api.devicehub.net

void setup() {
  Serial.begin(115200);
  delay(100);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  POST();
  GET();
}

void POST(void)
{
  delay(5000);
  ++value;// The value can be get from an analogic ou digital pin

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  pubString = "{\"value\": " + String(value) + "}";
  String pubStringLenght = String(pubString.length(), DEC);
  // We now create a URI for the request
  Serial.print("Requesting POST: ");
  // This will send the request to the server
  client.println("POST /v2/project/YOURPROJECTID/device/DEVICEUUID/sensor/SENSORNAME/data HTTP/1.1");
  client.println("Host: api.devicehub.net");
  client.print("X-ApiKey: YOURAPIKEY\r\n");
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.print("Content-Length: ");
  client.println(pubString.length());
  client.println();
  client.print(pubString);
  client.println();
  delay(500);

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
}

void GET(void)
{
  int state_pos;
  String state;
  delay(5000);
  ++value;// The value can be get from an analogic ou digital pin
  Serial.print("connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  pubString = "{\"value\": " + String(value) + "}";
  String pubStringLenght = String(pubString.length(), DEC);
  // We now create a URI for the request
  Serial.print("Requesting GET: ");
  // This will send the request to the server
  client.println("GET /v2/project/YOURPROJECTID/device/DEVICEUIID/actuator/ACTUATORNAME/state HTTP/1.1");
  client.println("Host: api.devicehub.net");
  client.print("X-ApiKey: YOURAPIKEY\r\n");
  client.println("Connection: close");
  client.println();
  delay(500);
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    state_pos=line.indexOf("state");
    if(state_pos>0)
    state=line.substring(state_pos+7,state_pos+8);
    else
    state="nada";
    Serial.println(state);
    //Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
}
