#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);

  if(!lox.begin()){
    Serial.println("VL53L0X connection error");
    while(1);
  }

  /*
    Available modes:
    VL53L0X_SENSE_DEFAULT
    VL53L0X_SENSE_LONG_RANGE
    VL53L0X_SENSE_HIGH_SPEED
    VL53L0X_SENSE_HIGH_ACCURACY
  */

  lox.configSensor(lox.VL53L0X_SENSE_LONG_RANGE);

  
  /*
    there are various modes that can be set via setDeviceMode()
    we are using the most basic.
  */

  lox.startRangeContinuous();
}

void loop() {
  if (lox.isRangeComplete()) {
    Serial.println(lox.readRange()); //mm
  }
}
