// Define pin numbers for ultrasonic sensors
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;
const int trigPin3 = 6;
const int echoPin3 = 7;

// Define pin numbers for motor driver
const int motor1Pin1 = 8;
const int motor1Pin2 = 9;
const int motor2Pin1 = 10;
const int motor2Pin2 = 11;

// Define constants
const int maxDistance = 20;  // Maximum distance to consider for obstacle detection (in cm)

// Function prototypes
long getDistance(int trigPin, int echoPin);
void moveForward();
void stop();
void turnLeft();
void turnRight();

void setup() {
  // Initialize pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  long distance1 = getDistance(trigPin1, echoPin1);
  long distance2 = getDistance(trigPin2, echoPin2);
  long distance3 = getDistance(trigPin3, echoPin3);

  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.print(" cm\t");
  Serial.print("Distance2: ");
  Serial.print(distance2);
  Serial.print(" cm\t");
  Serial.print("Distance3: ");
  Serial.print(distance3);
  Serial.println(" cm");

  if (distance1 < maxDistance) {
    // Obstacle detected in front
    if (distance2 < maxDistance) {
      // Obstacle detected on the left
      if (distance3 < maxDistance) {
        // Obstacle detected on the right
        stop();
        delay(1000);
        turnLeft();
        delay(1000);
      } else {
        turnRight();
        delay(1000);
      }
    } else {
      moveForward();
    }
  } else {
    moveForward();
  }
}

long getDistance(int trigPin, int echoPin) {
  // Trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) / 29.1;  // Convert to cm

  return distance;
}

void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void stop() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}
