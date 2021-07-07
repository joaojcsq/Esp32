#include <Arduino.h>

const int pinoSensor = 15;
bool s_high = false;
//unsigned long counter = 0;

void setup() {
  Serial.begin(115200);   
  pinMode(pinoSensor, INPUT);
}

void loop() { 
  // Zero = Branco
  if(digitalRead(pinoSensor)) s_high = true;

  if(!digitalRead(pinoSensor) && s_high){
    s_high = false;
    //counter += 1;
    Serial.println("1");
  }
delay(50);
//Serial.println(counter);
}
