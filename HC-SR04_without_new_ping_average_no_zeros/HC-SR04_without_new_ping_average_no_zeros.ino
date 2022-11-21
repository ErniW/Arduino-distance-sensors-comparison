#define TRIG_PIN 12
#define ECHO_PIN 11

#include "Average.h"

Average* average = new Average(8);

void setup(){
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop(){
  average->append(getDistance(TRIG_PIN,ECHO_PIN));

  Serial.println(average->get());
  //average->printArray();
  delay(50);
}
 
int getDistance(int trigPin, int echoPin){
  long duration, distance;
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH, 20000);

  if(duration == 0){
    pinMode(echoPin, OUTPUT);
    digitalWrite(echoPin, LOW);
    delayMicroseconds(200);
    pinMode(echoPin, INPUT); 
  }
  
  distance = (duration/2) / 29.1;
  
  return distance;
}
