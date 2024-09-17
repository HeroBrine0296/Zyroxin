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

char command;              // For storing Bluetooth commands
bool bluetoothControl = false;  // Switch between Bluetooth control and Trémaux's mode

// Path tracking variables for Trémaux's algorithm
bool pathMarked[4] = {false, false, false, false}; // 0: Forward, 1: Left, 2: Right, 3: Backward

void setup() {
  // Initialize motor and sensor pins
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

  // Initialize serial for debugging and Bluetooth (HC-05 uses Serial)
  Serial.begin(9600);
  Serial.println("Zyroxin Initialized: Ready for Bluetooth and Trémaux mode.");
}

void loop() {
  // Check for Bluetooth commands
  if (Serial.available() > 0) {
    command = Serial.read();
    handleBluetoothCommand(command);
  }

  // Trémaux's Algorithm if Bluetooth control is disabled
  if (!bluetoothControl) {
    int distanceFront = getDistance(trigPin1, echoPin1);
    int distanceLeft = getDistance(trigPin2, echoPin2);
    int distanceRight = getDistance(trigPin3, echoPin3);

    updatePathMarkers(distanceFront, distanceLeft, distanceRight);

    // Decision making in Trémaux's algorithm
    if (!pathMarked[0] && distanceFront > 10) {
      moveForward();
      pathMarked[0] = true; // Mark forward path
      Serial.println("Moving Forward - Trémaux's Mode");
    } else if (!pathMarked[1] && distanceLeft > 10) {
      turnLeft();
      pathMarked[1] = true; // Mark left path
      Serial.println("Turning Left - Trémaux's Mode");
    } else if (!pathMarked[2] && distanceRight > 10) {
      turnRight();
      pathMarked[2] = true; // Mark right path
      Serial.println("Turning Right - Trémaux's Mode");
    } else {
      moveBackward();
      Serial.println("Backtracking - Trémaux's Mode");
    }
  }

  delay(100);  // Short delay for stability
}

// Handle Bluetooth commands
void handleBluetoothCommand(char cmd) {
  switch (cmd) {
    case 'F': 
      moveForward();
      Serial.println("Bluetooth Command: Moving Forward");
      break;
    case 'B': 
      moveBackward();
      Serial.println("Bluetooth Command: Moving Backward");
      break;
    case 'L': 
      turnLeft();
      Serial.println("Bluetooth Command: Turning Left");
      break;
    case 'R': 
      turnRight();
      Serial.println("Bluetooth Command: Turning Right");
      break;
    case 'S': 
      stopMovement();
      Serial.println("Bluetooth Command: Stop");
      break;
    case 'X': 
      bluetoothControl = true;  // Switch to Bluetooth manual mode
      Serial.println("Bluetooth Control Enabled: Manual Mode Activated");
      break;
    case 'Y': 
      bluetoothControl = false;  // Switch back to Trémaux's algorithm
      Serial.println("Trémaux's Algorithm Enabled: Autonomous Mode Activated");
      break;
  }
}

// Distance measurement using ultrasonic sensors
int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.0344 / 2; // Convert to cm
  return distance;
}

// Update path markers for Trémaux's algorithm
void updatePathMarkers(int distanceFront, int distanceLeft, int distanceRight) {
  const int obstacleThreshold = 10; // cm

  pathMarked[0] = (distanceFront <= obstacleThreshold);  // Forward
  pathMarked[1] = (distanceLeft <= obstacleThreshold);   // Left
  pathMarked[2] = (distanceRight <= obstacleThreshold);  // Right
}

// Movement functions
void moveForward() {
  analogWrite(motor1Pin1, 255);  // Full speed forward
  analogWrite(motor1Pin2, 0);
  analogWrite(motor2Pin1, 255);  // Full speed forward
  analogWrite(motor2Pin2, 0);
}

void moveBackward() {
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 255);  // Full speed backward
  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 255);  // Full speed backward
}

void turnLeft() {
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 255);  // Left motor backward
  analogWrite(motor2Pin1, 255);  // Right motor forward
  analogWrite(motor2Pin2, 0);
}

void turnRight() {
  analogWrite(motor1Pin1, 255);  // Left motor forward
  analogWrite(motor1Pin2, 0);
  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 255);  // Right motor backward
}

void stopMovement() {
  analogWrite(motor1Pin1, 0);
  analogWrite(motor1Pin2, 0);  // Stop both motors
  analogWrite(motor2Pin1, 0);
  analogWrite(motor2Pin2, 0);
}
