const int trigPin = 9;
const int echoPin = 8;

const int redPin = 11;
const int greenPin = 10;
const int bluePin = 6;

const int buzzerPin = 3;

float previousDistance = 0.0;      
unsigned long previousMillis = 0; 

const float velocityThreshold = 1.00;
float closestDist = 10.0;

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
  
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2; 
  return distance;
}

// New function: averages 5 distance readings
float getAverageDistance() {
  const int numReadings = 5;
  float sum = 0;
  for (int i = 0; i < numReadings; i++) {
    sum += getDistance();
    delay(35); // Small delay between readings
  }
  return sum / numReadings;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // Use the average of 5 readings for improved accuracy
  float currentDistance = getAverageDistance();
  unsigned long currentMillis = millis();
  
  // Initialize baseline values on the first loop iteration
  if (previousMillis == 0) {
    previousDistance = currentDistance;
    previousMillis = currentMillis;
    delay(100);
    return;
  }
  
  float dt = (currentMillis - previousMillis) / 1000.0;
  float velocity = (currentDistance - previousDistance) / dt;
      
  String status = "";
  
  if (currentDistance > 10) {
    status = "Safe";
    setColor(0, 255, 0); 
    digitalWrite(buzzerPin, LOW);
    closestDist = 10.0;
  }
  else {
    if ((abs(velocity) > velocityThreshold) && (currentDistance < closestDist)) {
      status = "Close";
      setColor(255, 0, 0);
      tone(buzzerPin, 1000);
      delay(100);
      noTone(buzzerPin);
      delay(100);   
      closestDist = currentDistance;
    } 
    else {
      status = "Close";
      setColor(255, 170, 0); 
      digitalWrite(buzzerPin, LOW);
      closestDist = currentDistance;
    }
  }
  
  Serial.print("Distance: ");
  Serial.print(currentDistance);
  Serial.print(" cm    ");
  Serial.println(status);
  
  previousDistance = currentDistance;
  previousMillis = currentMillis;

  delay(100);
}
