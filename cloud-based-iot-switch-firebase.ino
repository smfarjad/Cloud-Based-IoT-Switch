# Contributor: Sheikh Muhammad Farjad
# Email: smfarjad@outlook.com
# Site: smfarjad.github.io/
# GitHub: github.com/smfarjad/

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "ss159-41f73.firebaseio.com"                     // Replace the quoted text with you firebase project URL
#define FIREBASE_AUTH "7VJJraJpK6PNsxYfiG7QOANdLvkklbzUZZ0PTA03"       // Replace the quoted text with your firebase authentication tokken
#define WIFI_SSID "VT-001"                                             // Replace the quoted text with your WiFi SSID
#define WIFI_PASSWORD "RFID3698*"                                      // Replace the quoted text with WiFi password
#define Relay 14 //D6                                                  // Specifying the pin connected with signal pin of relay (TRIAC or Opto-isolator)

int val;                                                               // State variable


void setup()
{
  Serial.begin(9600);                                                   
  pinMode(Relay, OUTPUT);

  digitalWrite(Relay, HIGH);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.setInt("S1", 0);                     // The same variables (i.e., S1) should be used in the android app while using Firebase SDK

}

void firebasereconnect()
{
  Serial.println("Reconnecting...");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  if (Firebase.failed())
  {
    Serial.print("Failed to connect:");
    Serial.println(Firebase.error());
    firebasereconnect();
    return;
  }

val = Firebase.getString("S1").toInt();                               // Reading the status of variable 'S1' from the firebase to take respective actions of switching on or off the relay.

  if (val == 1)                                                     
  {
    digitalWrite(Relay, LOW);
    Serial.println("light 1 ON");
  }
  else if (val == 0)                                                 
  {
    digitalWrite(Relay, HIGH);
    Serial.println("light 1 OFF");
  }


}
