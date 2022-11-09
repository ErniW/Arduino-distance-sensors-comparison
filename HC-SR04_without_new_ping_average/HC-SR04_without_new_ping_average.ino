#define TRIG_PIN 12
#define ECHO_PIN 11

int measurements[10];

void setup(){
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop(){
  int average = computeAverage(measurements, 10);

  Serial.println(average);
  delay(30);
}

int computeAverage(int* arr, size_t size){
  int total = 0;
  int newMeasurement = getDistance(TRIG_PIN, ECHO_PIN);

  for(int i=size-1; i>=0; i--){
    arr[i+1] = arr[i];
    total += arr[i+1];
  }

  arr[0] = newMeasurement;
  total += newMeasurement;

  return total / size;

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