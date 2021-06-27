#include <Arduino.h>

#define LED_PIN 2

String readString;

void setup() {
  Serial.begin(115200);           //Initializing the Serial Port to Baud rate 115200
  pinMode(LED_PIN, OUTPUT);      //Defining the Led pin as output 
}

void loop() {

  while (Serial.available()) {
    delay(3);  
    char c = Serial.read();
    readString += c; 
  }
  readString.trim();
  if (readString.length() >0) {
      
    if (readString == "on"){
      Serial.println("switching on");
      digitalWrite(LED_PIN, HIGH);
    }
    if (readString == "off")
    {
      Serial.println("switching off");
      digitalWrite(LED_PIN, LOW);
    }

    readString="";
  } 
}
