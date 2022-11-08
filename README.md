**A series of tests made together with students for the purpose of Tangible Interaction Design classes at Industrial Design faculty. I decided to put it online as a reference for future projects.**

## Sensors tested:
### Ultrasonic sensors:
- **HC-SR04**: We had two kinds of these. We've tested various tricks to improve their measurements.
- **Sparkfun HC-SR04**: to compare the quality with cheaper ones. *Is it worth it?*
- **DFRobot Gravity URM07**
- **DFRobot Gravity URM09**
- **DFRobot Gravity URM37 v5**

### Infrared sensors:
- **Sharp GP2Y0A41SK0F**
- **Sharp GP2Y0A21YK0F**

### Time of Flight sensors:
- **GY-VL53L0X**
- **Pololu VL53L3CX**: *There are no Arduino Libraries or registers documentation available. Tested on STM32F446RE with ST firmware.*

## Testing conditions:
### Locations:
- Open space.
- Hallway wide and narrow.
- On a table.

*We've tried to test with and without background elements.*

### Measurments:
*We've measured different kind of objects with:*
- Flat surface.*
- Uneven surface.*
- Narrow object.
- Material.
- Hand movement.
- Pedestrian.

**Small and larger object.*

## Review of results:

### HC-SR04
**How to fix the problem with freezing?**
There are many variants of this sensor. However, the cheapest one has issues you can read about here: http://www.therandomlab.com/2015/05/repair-and-solve-faulty-hc-sr04.html to be honest using it without the proposed solutions is worthless.
- Use the included code according to mentioned article (it's in comment section!).
- Solder the 10k resistor according to the picture.
- Use quick and dirty solution to reset the sensor by switching it on and off via transistor. Use it only with long intervals of measurements, you probably decrease its lifetime by a significant value.

*Using the new ping library without any fixes seems resonable with the HC-SR04 from Sparkfun, other will eventually hang and return zeroes.*

*On greater distances sensor will sometimes returns zeroes no matter what. Depending on project you can discard the zeroes or measure an average of values.*

****
- Maximum range: Depending on vendor you can read it has up to 4 meters range. There is no way to use it effectively for distance over approx two meters unless you measure a distance to a wall.
- 

### VL53L0X

- Maximum range:


### Pololu VL53L3CX
*Because of the way it works,* **the sensor can't be used with Arduino boards at all.** I've tested it on my STM32 Nucleo F446RE with ARM Cortex M4 with STM32Duino library, but everything mentioned is out of scope for our classes. What is more - I don't feel competent enough to do reverse-engineering of ST propertiary driver from scratch.*

*VL53LCX measures distance through computing histogram making it capable of measuring multiple objects within its field of view and returning their distances. Unfortunately there must be a significant difference between them. You can download STM32Duino VL53L3CX library in your library manager..*

- **Maximum range: 310cm indoor / 100cm  outdoor** *(Datasheet 5.3)* measured in scale of milimeters. The only interference is the sunlight which dramatically drops the max distance and accuracy.
- **Detects thin object and works fine with soft materials, but requires calibration offset.**

**Tips on STM32duino and VL53L3CX:**
- *Here is the guide to install https://github.com/stm32duino/wiki/wiki/Getting-Started you also need to install STM32CubeProgrammer and include it into system's PATH*
- *VL53L3CX XSHUT pin is XSDN_I according to example sketch.*
- *Actually the address 0x12 is assigned on runtime. Default i2c address is 0x52. You don't need to change it.*
- *VL53L3CX pins aren't 5V compatible. Pololu board has voltage regulator but they wrote that XSHUT and GPIO1 aren't level-shifted.*
- *TODO: add calibration code.*