#define TRIG_PIN 12
#define ECHO_PIN 11

void setup(){
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

int zeroCounter = 0;
int distance = 0;

void loop(){
  int newDistance = getDistance(TRIG_PIN, ECHO_PIN);

  if(newDistance == 0) zeroCounter++;
  else {
    zeroCounter = 0;
    distance = newDistance;
  }

  if(zeroCounter >= 4) Serial.println(0);
  else Serial.println(distance);

  delay(100);
}
 
int getDistance(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000);
  int distance = duration * 0.034 / 2;

  if(duration == 0){
    pinMode(echoPin, OUTPUT);
    digitalWrite(echoPin, LOW);
    delayMicroseconds(200);
    pinMode(echoPin, INPUT); 
  }

  return distance;
}