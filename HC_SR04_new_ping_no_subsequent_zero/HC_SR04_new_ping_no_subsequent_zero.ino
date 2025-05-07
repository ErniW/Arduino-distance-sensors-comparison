#include <NewPing.h>

//Subsequent zero values below threshold are treated as noise.
#define ZERO_THRESHOLD 5

#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int zeroCounter = 0;

void setup() {
  Serial.begin(9600);
}

int value = 0;

void loop() {

  int distance = sonar.ping_cm();
  
  if(distance == 0){
    zeroCounter++;
  }
  else{
    value = distance;
    zeroCounter = 0;
  }

  if(zeroCounter >  ZERO_THRESHOLD){
    value = 0;
  }

  Serial.println(value);
  delay(50);

}