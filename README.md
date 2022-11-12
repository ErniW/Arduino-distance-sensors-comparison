**A series of tests made together with students for the purpose of Tangible Interaction Design classes at Industrial Design faculty. I decided to put it online as a reference for future projects.**

*I didn't put all sensors code because some libraries and code examples provided are straightforward*

## Sensors tested:
### Ultrasonic sensors:
- **HC-SR04**: We had two kinds of these. We've tested various tricks to improve their measurements.
- **DFRobot Gravity URM07**
- **DFRobot Gravity URM09**
- **DFRobot Gravity URM37 v5**

### Infrared sensors:
- **Sharp GP2Y0A41SK0F**
- **Sharp GP2Y0A21YK0F**

### Time of Flight sensors:
- **GY-VL53L0X**
- **Pololu VL53L3CX**: *There are no Arduino libraries or registers documentation available. Tested on STM32F446RE and STM32duino.*

### Gesture sensors:
- **APDS-9960**: *Detects Left/Right/Forward/Back/Up/Down gestures.*

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

# Review of results:

## HC-SR04
Before using this sensor, **lower your expectations, otherwise the disappointment will hit you hard. People who praises the quality of sensor use them in particular case measuring large and flat objects.** Sensor gives a good result if it gets them, which is difficult.

### Maximum range:
- **Depending on vendor's datasheet it has up to 4 meters range but there is no way to use it effectively for distance over approx 2 meters unless you measure a distance to a large flat object like a car or a wall.**
- If your project is controlled via hand, after 50cm it will have difficulties detecting it.
- 250cm is fine to measure a person walking toward your project.

### How to fix the problem with hanging zeroes?
There are many variants of this sensor. However, chepest version has issues you can read about here: http://www.therandomlab.com/2015/05/repair-and-solve-faulty-hc-sr04.html **to be honest using it without the proposed solutions is worthless.**
- Use the included code according to mentioned article (it's in comment section!). I made some modifications to it.
- Solder the 10k resistor according to the picture.
- Add 100uf capacitor.
- Other solution I found personally: Use quick and dirty solution to reset the sensor by switching it on and off via transistor. Use it only with long intervals of measurements, you probably decrease its lifetime by a significant value.

There is a library named New Ping. Notice how single and multiple sensors are declared.

### Notes:
- *Using the New Ping library without any fixes seems resonable with the HC-SR04 from Sparkfun, other (the cheapest) will eventually hang and return zeroes.*
- *The sensor will sometimes returns zeroes no matter what. Depending on project you can discard the zeroes or measure an average of values. Using constrains in your code to limit the distance only to what you want to measure - for example hand between 5cm and 50cm.*
- **Sensor is fine for learning or very basic usage in most cases (but not all). Otherwise it will be unbearable. You should aim for different sensor when trying to control something with hands or detect small objects.**
- *It can't measure thin objects and catches noise from narrow and messy locations. Based on my experience many soft materials are a challenge.*
- *Reading many sensors can be slow. Computing averages of results to reduce noise would be O(M * N) slower.*
- *Hacks mentioned makes the sensor work louder, you can hear the clicks.*
- *The sensor accuracy can be improved with thermometer (speed of sound vary with changes in air temperature).*

## DFRobot Gravity URM07
https://wiki.dfrobot.com/URM07-UART_Ultrasonic_Sensor_SKU__SEN0153
### Maximum range: 
**20-750cm**
### Notes:
- *URM07 has built-in temperature sensor.*
- *URM07 communicates via Serial.*
- *Detecting angle is 60 degrees, it's important if you intentionally want to detect surrounding things.*
- *You can have many of sensors on single bus by changing their addresses.*

## DFRobot Gravity URM09
https://wiki.dfrobot.com/URM09_Ultrasonic_Sensor_(Gravity-I2C)_(V1.0)_SKU_SEN0304
### Maximum range:
**2-500cm** There are different ranges 150, 300, 500. According to documentation lower range will reduce sensitivity?
### Notes:
- *URM09 communicates via i2c. It also has its analog equivalent available to purchase.*
- *URM09 has built-in temperature sensor.*

## DFRobot Gravity URM37 v5
https://wiki.dfrobot.com/URM37_V5.0_Ultrasonic_Sensor_SKU_SEN0001_
### Maximum range:
**2-800cm**
### Notes:
- *URM37 communicates via Serial but it has various operation modes. It has additional features comparing it to other DFRobot sensors mentioned above.*
- *URM37 has built-in temperature sensor.*
- *URM37 has a button to switch from Serial (TTL) to RS232 communication. Do not play with that!*

## Sharp GP2Y0A41SK0F and Sharp GP2Y0A21YK0F
*Sensors are similar.*

### Maximum range:
- **GP2Y0A41SK0F: 4-30cm**
- **GP2Y0A21YK0F: 10-80cm**

**For both you can use SharpIR Arduino library**, if you check the library .cpp file you will see how simple is the measurement equation.

### Notes:
- **Analog sensors win in terms of simplicity of connection and they're very accurate.**
- *They have a large blind spot (13.3% / 12.5% of their total range).*
- *Theoretically you can compute polynomial regression model to calibrate your sensor to improve accuracy. I guess my students aren't proficient in machine learning nor statistics so I won't explain it further.*
- *Sunlight can cause noise in measurements.*

## VL53L0X

TODO: Figure out how to calibrate the sensor to check the difference. Without calibration sensor is fine.

### Maximum range:
- **120cm in standard and high accuracy mode.** *(approx. 1m effective)*
- **200cm in long range mode.**
- Hand movement: 80cm in long range, 50 in high accuracy or default.
- Very thin object up to 30-35 cm.

### Notes:
- **They're relatively cheap comparing to what they offer if you buy a no-name board rather than Adafruit.**
- **The cheap board (violet color) is the smallest among all which matters in some situations.**
- *You can use Adafruit library.*
- *Straightforward usage is a plus. You can choose between long range and high accuracy modes.*
- *Long range or high speed mode is not suitable for outdoor daylight. Outdoor usage cuts the accuracy and distance dramatically (Datasheet 5.3 Ranging Accuracy). Direct exposure to light can create noise in measurements.*
- *High accuracy mode is slow and even in that mode the value floats +/- 3mm so eventually the fact that sensor returns distance in milimeters won't give you that much. Maybe computing averages in faster modes make sense? Measurement frequency is faster than ultrasonic sensor.*
- *It is possible to calibrate the sensor but guidance is not provided through Adafruit library.*

## Pololu VL53L3CX
Because of the way it works, **the sensor can't be used with Arduino boards at all.** I've tested it on my STM32 Nucleo F446RE with ARM Cortex M4 with STM32Duino library, but everything mentioned is out of scope for our classes. What is more - I don't feel competent enough to do reverse-engineering of ST propertiary driver from scratch.

**VL53LCX measures distance through computing histogram making it capable of capturing multiple objects within its field of view and returning their distances separately.** Unfortunately there must be a significant difference between them.

- **Maximum range: 310cm indoor / 100cm  outdoor** *(Datasheet 5.3)* measured in scale of milimeters. The only interference is the sunlight which dramatically drops the max distance and accuracy.
- **Detects thin object and works fine with soft materials, but requires calibration offset (I measured the distance with ruler and it always had approx. 3cm too much no matter what kind of object was measured).**

### Tips on STM32duino and VL53L3CX:
- *Here is the guide to install https://github.com/stm32duino/wiki/wiki/Getting-Started you also need to install STM32CubeProgrammer and include it into system's PATH*
- *You can download STM32Duino VL53L3CX library in your library manager.*
- *VL53L3CX XSHUT pin is XSDN_I according to example sketch.*
- *Actually the address 0x12 is assigned on runtime. Default i2c address is 0x52. You don't need to change it.*
- *VL53L3CX pins aren't 5V compatible. Pololu board has voltage regulator but they wrote that XSHUT and GPIO1 aren't level-shifted.*
- *TODO: add calibration code.*

## APDS-9960
Measurement distance is up to 100mm (in my opinion it's up to 150mm), however the **measurements are raw IR light density values not distance units.**

It can measure up/down/left/right gestures and near/far when using proximity data.

### Notes:
- **Sensor operates in 3.3V logic, do not connect VCC to 5V. SDA and SCL will work on 5V however it's not recommended (you can use logic-level converter).**
- *There are libraries from Adafruit, Sparkfun and Arduino. Their example code looks similar. Some of them use interrupts so you can respond immediately whenever an event occurs instead of polling for it.* **Sparkfun library includes near/far gesture based on hand distance but Arduino library looks like is not blocking the main loop.**
- *Within the libraries it seems that measuring proximity and gestures doesn't play well with each other.*
- **PAJ7620U2** *seems to be an alternative, it computes the gesture internally?*