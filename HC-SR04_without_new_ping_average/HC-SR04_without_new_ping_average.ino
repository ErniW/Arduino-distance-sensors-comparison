#define TRIG_PIN 12
#define ECHO_PIN 11

#define BUFFER_SIZE 10

int valuesBuffer[BUFFER_SIZE];
int bufferHead = 0;

void setup(){
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop(){
  int value = getDistance(TRIG_PIN, ECHO_PIN);
  int average = updateAverage(value);

  Serial.println(average);
  delay(30);
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