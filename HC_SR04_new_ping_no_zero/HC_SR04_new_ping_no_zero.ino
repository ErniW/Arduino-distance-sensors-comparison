#include <NewPing.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = sonar.ping_cm();

  if(value != 0){
    //Do something when value is non-zero
    Serial.println(value);
  }
  else{
    //Remember that zero means two things: Out of range or too close.
    Serial.println("Zero detected!");
  }

  delay(50);
}