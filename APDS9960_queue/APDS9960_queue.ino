#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include "queue.h"

SparkFun_APDS9960 apds = SparkFun_APDS9960();

Queue* queue = new Queue(10);

void setup() {
  Serial.begin(9600);

  if(!apds.init()){
    Serial.println("APDS9960 connection error");
  }

  apds.enableGestureSensor(false);

  apds.setProximityGain(PGAIN_2X);
  apds.enableProximitySensor(false);
}

void loop() {

  unsigned long time = millis();

  if (apds.isGestureAvailable()) {
    queue->state = READING_GESTURE;
    int gesture = apds.readGesture();
    queue->push(gesture);
    queue->print();

    queue->lastTimeActive = time;
    queue->state = IDLE;
  }
  
  if(time - queue->lastTimeActive > 5000 && queue->state == IDLE){
    queue->state = CLEARING;
    queue->lastTimeActive = time;
  }

  if(time - queue->lastTimeActive > 1000 &&  queue->state == CLEARING){
    if(!queue->isEmpty()) {
      int val = queue->pop();
      Serial.print("Removing: ");
      queue->printDirection(val);
      Serial.println(' ');
      queue->print();
    }
    else{
      queue->state = IDLE;
    }
    
    queue->lastTimeActive = time;
  }

}