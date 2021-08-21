#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>
#include "ThingSpeak.h"

WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);
int ledState = LOW;   
int timezone = 7 * 3600;
int dst = 0;
int led ,statusCode;

unsigned long channel_number = 1483123;            // Channel ID
const char * read_api_key = "NGER6CXBD8DPA28H"; // Read API Key

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>

const char* ssid= "realme 3 Pro";
const char* pass="khusi123";
char auth[] = "r9rh-gCJ1eFq5lGDayHSsPNfI_uSzVcE";

int call=0;

WiFiClient  client;

BLYNK_WRITE(V0){
    call=param.asInt();
}

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
 Serial.begin(9600);
 WiFi.mode(WIFI_AP_STA);
 boolean result = WiFi.softAP("Wemos_AP", "Wemos_comm");
 if(result == true)
  {
    Serial.println("Ready");
  }
  else
  {
    Serial.println("Failed!");
  }
 WiFi.softAPConfig(IP, IP, mask);
 Blynk.begin(auth, ssid, pass);
 server.begin();
 Serial.println();
 Serial.println("Server started.");
  display.setFont();
  display.setTextSize(1);
  display.clearDisplay();
  display.setTextColor(WHITE);
Serial.print("check");
configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
while(!time(nullptr)){
Serial.print("*");
delay(500);
}
ThingSpeak.begin(client);
pinMode(D3,OUTPUT);
}
void loop() {
  Blynk.run();
// WiFiClient client = server.available();
// if (!client) {return;}
// String request = client.readStringUntil('\r');
// client.flush();
// client.println(request + "\r");
 time_t now = time(nullptr);
struct tm* p_tm = localtime(&now);

 long led = ThingSpeak.readIntField(channel_number, 1, read_api_key);
 statusCode = ThingSpeak.getLastReadStatus();
 if(led==1){
  if (statusCode == 200){
  Serial.println("khela");
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println("Someone is");
  display.setCursor(25,20);
  display.println("at the");
  display.setCursor(35,40);
  display.println("door");
  display.display();
  if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(D3, ledState);}
   else
  {
    Serial.println("Unable to read channel / No internet connection");
  }  
  
 }
 else if(call==1){
  Serial.println("khela2");
  display.clearDisplay();
  display.setCursor(10,0);
  display.setTextSize(2);
  display.println("Sweta is");
  display.setCursor(20,20);
  display.println("calling");
  display.setCursor(40,40);
  display.println("you");
  display.display();
   if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(D3, ledState);
 }
 else{
  Serial.println("lol");
  display.clearDisplay();
 
display.setTextSize(3);
display.setTextColor(WHITE);
 
display.setCursor(15,5);
if((p_tm->tm_min)+30 > 60){
display.print((p_tm->tm_hour)-1);
display.print(":");
if( (p_tm->tm_min)-30 <10)
display.print("0");
display.print((p_tm->tm_min)-30);  
}
else{
  display.print((p_tm->tm_hour)-2);
display.print(":");
if( (p_tm->tm_min)+30 <10)
display.print("0");
display.print((p_tm->tm_min)+30); 
}
 
 
display.setTextSize(1);
display.setCursor(25,40);
display.print(p_tm->tm_mday);
display.print(" Aug ");
display.print(p_tm->tm_year + 1900);
 
display.display();

 }
}
