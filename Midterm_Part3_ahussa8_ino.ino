#include <Servo.h>

Servo myservo;
const int servoPin = 5;  

const int trigPin = 9;
const int echoPin = 8;

const int buttonPin = 12;

const int redPin   = 11;
const int greenPin = 10;
const int bluePin  = 6;

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
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

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(buttonPin, INPUT_PULLUP);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  setColor(0, 255, 0);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    setColor(255, 0, 0);
    
    float bestDistance = 9999.0;
    int bestAngle = 90; 
    
    for (int angle = 0; angle <= 180; angle += 5) {
      myservo.write(angle);
      delay(100);  
      float d = getDistance();
      Serial.println(d);
      if ((d < bestDistance) && (d != 0.0)) {
        bestDistance = d;
        bestAngle = angle;
      }
    }
    
    // Point servo to the angle where the closest object was detected
    myservo.write(bestAngle);
    
    // Set LED to green to indicate scanning is complete
    setColor(0, 255, 0);
    
    // Wait for button release to avoid repeated scanning
    while (digitalRead(buttonPin) == LOW) {
      delay(50);
    }
    
    delay(100);
  }
}
