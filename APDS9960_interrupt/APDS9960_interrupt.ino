#include <Wire.h>
#include <SparkFun_APDS9960.h>
// #include <util/atomic.h>
// #include <avr/interrupt.h>

#define INTERRUPT_PIN 3

SparkFun_APDS9960 apds = SparkFun_APDS9960();

volatile bool gestureAvailable_flag = false;

void setup() {
  Serial.begin(9600);

  if (!apds.init()) {
    Serial.println("APDS9960 connection error");
  }

  pinMode(INTERRUPT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), apds_int, FALLING);

  apds.enableGestureSensor(true);
}

void apds_int() {
  gestureAvailable_flag = true;
}

void loop() {
  if (gestureAvailable_flag) {

    if (apds.isGestureAvailable()) {

      /*
        Prevent interrupting the measurements,

        I don't know why but using cli() and sei() or ATOMIC_BLOCK
        blocks the code indefinitely but attach/detach not.
        
      */

      detachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN));
      int gesture = apds.readGesture();

      switch (gesture) {
        case DIR_UP:
          Serial.println("UP");
          break;
        case DIR_DOWN:
          Serial.println("DOWN");
          break;
        case DIR_LEFT:
          Serial.println("LEFT");
          break;
        case DIR_RIGHT:
          Serial.println("RIGHT");
          break;
        case DIR_NEAR:
          Serial.println("NEAR");
          break;
        case DIR_FAR:
          Serial.println("FAR");
          break;
        default:
          Serial.println("NONE");
      }

      gestureAvailable_flag = false;
      attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), apds_int, FALLING);
 
    }
  }

}