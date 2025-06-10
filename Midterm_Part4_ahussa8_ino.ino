#include <Servo.h>

Servo myservo;
const int servoPin = 5;

const int trigPin = 9;
const int echoPin = 8;

const int redPin   = 11;
const int greenPin = 10;
const int bluePin  = 6;

const float objectLostThreshold = 10.0;

bool tracking = false;
int currentAngle = 90;

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
  myservo.attach(servoPin);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  setColor(255, 0, 0);
  myservo.write(90);
}

void loop() {
  if (!tracking) {
    setColor(255, 0, 0);
    float bestDistance = 9999.0;
    int bestAngle = 90;
    
    for (int angle = 0; angle <= 180; angle += 5) {
      myservo.write(angle);
      delay(100);
      float d = getDistance();
      if ((d != 0.0) && (d < bestDistance)) {
        bestDistance = d;
        bestAngle = angle;
      }
    }
    
    if (bestDistance < objectLostThreshold) {
      tracking = true;
      currentAngle = bestAngle;
      myservo.write(currentAngle);
      setColor(0, 255, 0);
      delay(100);
    }
  } else {
    int startAngle = currentAngle - 20;
    int endAngle   = currentAngle + 20;
    if (startAngle < 0) startAngle = 0;
    if (endAngle > 180) endAngle = 180;
    
    float bestDistance = 9999.0;
    int bestAngle = currentAngle;
    
    for (int angle = startAngle; angle <= endAngle; angle += 20) {
      myservo.write(angle);
      delay(80);
      float d = getDistance();
      if ((d != 0.0) && (d < bestDistance)) {
        bestDistance = d;
        bestAngle = angle;
      }
    }
    
    currentAngle = bestAngle;
    myservo.write(currentAngle);
    setColor(0, 255, 0);
    
    if (bestDistance > objectLostThreshold) {
      tracking = false;
      setColor(255, 0, 0);
      delay(100);
    }
    
    delay(100);
  }
}
