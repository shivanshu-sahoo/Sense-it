#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

const char* ssid= "realme 3 Pro";
const char* pass="khusi123";

int button=A0;

IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

unsigned long channel_number = 1483123;            // Channel ID
const char * write_api_key = "4CA24TGTXQAURD2I"; // Read API Key

void setup() {
  ThingSpeak.begin(client);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected");
  pinMode(A0,INPUT);
}
void loop() {
  int value=analogRead(A0);
  Serial.println(value);
  if(value>1000){
//  client.connect(server, 80);
//  Serial.println(client.print("1\r"));
//  String answer = client.readStringUntil('\r');
//  Serial.println("From the AP: " + answer);
//  client.flush();
//  client.stop();
  ThingSpeak.writeField(channel_number, 1, 1, write_api_key);
  }
  else
  ThingSpeak.writeField(channel_number, 1, 0, write_api_key);
}
