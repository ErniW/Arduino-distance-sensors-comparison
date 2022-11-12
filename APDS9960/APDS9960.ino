#include <Wire.h>
#include <SparkFun_APDS9960.h>

SparkFun_APDS9960 apds = SparkFun_APDS9960();

uint8_t proximity_data = 0;

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
  if (apds.isGestureAvailable()) {
      switch (apds.readGesture()) {
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
  }
}
