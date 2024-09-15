// Define pins for motors and sensors
const int motor1Pin1 = 3;  // L298N IN1
const int motor1Pin2 = 4;  // L298N IN2
const int motor2Pin1 = 5;  // L298N IN3
const int motor2Pin2 = 6;  // L298N IN4
const int trigPin1 = 7;    // Front ultrasonic sensor
const int echoPin1 = 8;
const int trigPin2 = 9;    // Left ultrasonic sensor
const int echoPin2 = 10;
const int trigPin3 = 11;   // Right ultrasonic sensor
const int echoPin3 = 12;

// Path tracking variables
bool pathMarked[4] = {false, false, false, false}; // 0: Forward, 1: Left, 2: Right, 3: Backward

void setup() {
pinMode(motor1Pin1, OUTPUT);
pinMode(motor1Pin2, OUTPUT);
pinMode(motor2Pin1, OUTPUT);
pinMode(motor2Pin2, OUTPUT);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);

Serial.begin(9600);
}

void loop() {
int distanceFront = getDistance(trigPin1, echoPin1);
int distanceLeft = getDistance(trigPin2, echoPin2);
int distanceRight = getDistance(trigPin3, echoPin3);

updatePathMarkers(distanceFront, distanceLeft, distanceRight);

// Decision making based on path markers and distances
if (!pathMarked[0] && distanceFront > 10) {
// Move forward if the path ahead is clear and not marked
moveForward();
pathMarked[0] = true; // Mark the forward path as taken
pathMarked[1] = false; // Unmark left and right paths
pathMarked[2] = false;
} else if (!pathMarked[1] && distanceLeft > 10) {
// Turn left if the left path is clear and not marked
turnLeft();
pathMarked[1] = true; // Mark the left path as taken
pathMarked[0] = false; // Unmark forward path
pathMarked[2] = false;
} else if (!pathMarked[2] && distanceRight > 10) {
// Turn right if the right path is clear and not marked
turnRight();
pathMarked[2] = true; // Mark the right path as taken
pathMarked[0] = false; // Unmark forward path
pathMarked[1] = false;
} else {
// Backtrack if all paths are marked or blocked
moveBackward();
pathMarked[0] = false; // Unmark the forward path
pathMarked[1] = false; // Unmark left path
pathMarked[2] = false; // Unmark right path
}

delay(100); // Short delay to allow for movement and sensor readings
}

int getDistance(int trigPin, int echoPin) {
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

long duration = pulseIn(echoPin, HIGH);
int distance = duration  0.0344 / 2; // Convert to cm

return distance;
}

void updatePathMarkers(int distanceFront, int distanceLeft, int distanceRight) {
const int obstacleThreshold = 10; // cm

// Update path markers based on distance readings
pathMarked[0] = (distanceFront <= obstacleThreshold);

// Forward
pathMarked[1] = (distanceLeft <= obstacleThreshold);  // Left
pathMarked[2] = (distanceRight <= obstacleThreshold); // Right
}

void moveForward() {
analogWrite(motor1Pin1, 255); // Full speed
analogWrite(motor1Pin2, 0);
analogWrite(motor2Pin1, 255); // Full speed
analogWrite(motor2Pin2, 0);
}

void turnRight() {
analogWrite(motor1Pin1, 255); // Full speed
analogWrite(motor1Pin2, 0);
analogWrite(motor2Pin1, 0);
analogWrite(motor2Pin2, 255); // Full speed
}

void turnLeft() {
analogWrite(motor1Pin1, 0);
analogWrite(motor1Pin2, 255); // Full speed
analogWrite(motor2Pin1, 255); // Full speed
analogWrite(motor2Pin2, 0);
}

void moveBackward() {
analogWrite(motor1Pin1, 0);
analogWrite(motor1Pin2, 255); // Full speed
analogWrite(motor2Pin1, 0);
analogWrite(motor2Pin2, 255); // Full speed
}

