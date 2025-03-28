#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define MAX_DISTANCE 200

#define BUFFER_SIZE 10

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int valuesBuffer[BUFFER_SIZE];
int bufferHead = 0;

void setup(){
  Serial.begin(9600);
}

void loop(){
  int value = sonar.ping_cm();
  int average = updateAverage(value);

  Serial.println(average);
  delay(50);
}

int updateAverage(int value){
  valuesBuffer[bufferHead] = value;
  bufferHead++;
  bufferHead %= BUFFER_SIZE;

  int total = 0;

  for(int i=0; i<BUFFER_SIZE; i++){
    total += valuesBuffer[i];
  }

  return total / BUFFER_SIZE;
}