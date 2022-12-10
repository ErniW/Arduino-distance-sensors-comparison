#include <SoftwareSerial.h>

#define RX_PIN 10
#define TX_PIN 11

#define header_H    0x55 //Header
#define header_L    0xAA //Header
#define device_Addr 0x11 //Address
#define data_Length 0x00 //Data length
#define get_Dis_CMD 0x02 //Command: Read Distance
#define checksum    (header_H+header_L+device_Addr+data_Length+get_Dis_CMD)

#define baudRate9600_H 0x03
#define baudRate9600_L 0x1C

SoftwareSerial URM07(RX_PIN, TX_PIN);

uint8_t receiveDistanceBuffer[8];

void setup(){
  Serial.begin(9600);
  URM07.begin(19200);
  setBaudRate();
  URM07.begin(9600);
}

void loop(){
  unsigned int distance = readValue();
  Serial.println(distance);
  delay(80);
}

unsigned int readValue(){
  char getDistanceCommand[6] = {
    header_H,
    header_L,
    device_Addr,
    data_Length,
    get_Dis_CMD,
    checksum
  };

  for(int i=0; i<6; i++){
    URM07.write(getDistanceCommand[i]);
  }

  int j = 0;
  while(URM07.available()){
    receiveDistanceBuffer[j++] = URM07.read();
  }

  return ((receiveDistanceBuffer[5] << 8) | receiveDistanceBuffer[6]);
}

void setBaudRate(){
  URM07.write(header_H);
  URM07.write(header_L);
  URM07.write(device_Addr);
  URM07.write(0x01);
  URM07.write(0x08);
  URM07.write(baudRate9600_H);
  URM07.write(baudRate9600_L);
}