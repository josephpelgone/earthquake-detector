#include "twilio.hpp"

#define RXp2 16
#define TXp2 17

const char *SSID = "HUAWEI-B56e";
const char *PASSWORD = "xtNW3NNf";

const char *ACCOUNT_SID = "AC23aa90f258678a28a66c8e4be467aff7";
const char *AUTH_TOKEN = "21701a3924d56b2b4175552c48b24bfa";
const char *FROM_NUMBER = "+13253088895";

const char *TO_NUMBER = "+639477382408";
const char *MESSAGE = "EARTHQUAKE DETECTED";

Twilio *twilio;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
}

void loop() {
  while (Serial2.available() == 0) {} 
  String teststr = Serial2.readString();
  teststr.trim();
  if(teststr == "DETECTED") {
    Serial.println(teststr);
    sendSMS();
  }
}

void sendSMS(){
   // put your main code here, to run repeatedly:
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(500);
  }
  
  Serial.println("Connected!");
  twilio = new Twilio(ACCOUNT_SID, AUTH_TOKEN);
  delay(1000);
  String response;
  bool success = twilio->send_message(TO_NUMBER, FROM_NUMBER, MESSAGE, response);
  if (success) {
    Serial.println("Sent message successfully!");
  } else {
    Serial.println(response);
  }  
}
