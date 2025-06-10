#include <Servo.h>

Servo myservo;
const int servoPin = 5;

const int trigPin = 9;
const int echoPin = 8;

const int detectionThreshold = 10;

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000);
  float distance = duration * 0.034 / 2;
  return distance;
}

void loop() {
  bool leftDetected   = false;
  bool centerDetected = false;
  bool rightDetected  = false;
  
  myservo.write(0);
  delay(250); 
  if (getDistance() < detectionThreshold) {
    leftDetected = true;  
  }
  
  // Scan center
  myservo.write(90);
  delay(250);
  if (getDistance() < detectionThreshold) {
    centerDetected = true;
  }
  
  myservo.write(180);
  delay(250);
  if (getDistance() < detectionThreshold) {
    rightDetected = true;  
  }

  myservo.write(90);  
  delay(250);
  
  String situation = "";
  if (leftDetected && centerDetected && rightDetected) {
    situation = "Dead end";
  } else if (leftDetected && centerDetected && !rightDetected) {
    situation = "in Right corner";  
  } else if (!leftDetected && centerDetected && rightDetected) {
    situation = "in Left corner";  
  } else if (leftDetected && !centerDetected && !rightDetected) {
    situation = "Wall on the Right";  
  } else if (!leftDetected && !centerDetected && rightDetected) {
    situation = "Wall on the Left";  
  } else if (!leftDetected && !centerDetected && !rightDetected) {
    situation = "Open space";
  } else if (!leftDetected && centerDetected && !rightDetected) {
    situation = "Facing Wall";
  } else if (leftDetected && !centerDetected && rightDetected) {
    situation = "Corridor";
  } else {
    situation = "Undefined";
  }
  
  Serial.println(situation);
}
