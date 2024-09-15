# Zyroxin Robot

Zyroxin is an Arduino-based maze-solving robot designed for educational purposes and hobbyist projects. This repository contains all the necessary information to build and program your own Zyroxin robot.

## Table of Contents
1. [Specifications](#specifications)
2. [Components](#components)
3. [Assembly Instructions](#assembly-instructions)
4. [Circuit Diagram](#circuit-diagram)
5. [Arduino Code](#arduino-code)
6. [Contributing](#contributing)
7. [License](#license)

## Specifications

- **Dimensions:**
  - Length: 19.75 cm
  - Width: 15.2 cm
  - Height: 10.5 cm
- **Weight:** 250g - 500g

## Components

- Arduino Board (Arduino Uno or Nano)
- L298N Motor Driver
- 2 DC Motors (for movement)
- 3 Ultrasonic Sensors (for obstacle detection)
- Caster Wheel (for rotation)
- 12V Battery (for power supply)
- Jumper wires
- Robot chassis

## Assembly Instructions

1. **Prepare Components**
   - Gather all the components listed above.

2. **Assemble the Mechanical Parts**
   - Attach DC motors to the robot chassis.
   - Connect the wheels to the motors.
   - Install the caster wheel at the rear of the chassis for stability and rotation.

3. **Connect the Electronics**
   - **Motor Driver Connections:**
     - VCC → External 12V Power Supply
     - GND → GND of External Power Supply and Arduino
     - IN1 → Pin 3 of Arduino
     - IN2 → Pin 4 of Arduino
     - IN3 → Pin 5 of Arduino
     - IN4 → Pin 6 of Arduino

   - **Motor Connections (L298N):**
     - Motor 1 (Left Motor):
       - OUT1 → One terminal of Left Motor
       - OUT2 → Other terminal of Left Motor
     - Motor 2 (Right Motor):
       - OUT3 → One terminal of Right Motor
       - OUT4 → Other terminal of Right Motor

   - **Ultrasonic Sensor Connections:**
     - Front Sensor:
       - VCC → 5V of Arduino
       - GND → GND of Arduino
       - Trig → Pin 7 of Arduino
       - Echo → Pin 8 of Arduino
     - Left Sensor:
       - VCC → 5V of Arduino
       - GND → GND of Arduino
       - Trig → Pin 9 of Arduino
       - Echo → Pin 10 of Arduino
     - Right Sensor:
       - VCC → 5V of Arduino
       - GND → GND of Arduino
       - Trig → Pin 11 of Arduino
       - Echo → Pin 12 of Arduino

4. **Upload the Code**
   - Open the Arduino IDE and copy the provided code into a new sketch.
   - Select the correct board and port in the Arduino IDE.
   - Upload the code to the Arduino board.

5. **Testing and Calibration**
   - Power on the robot and ensure all connections are secure.
   - Verify that the robot moves forward, backward, and turns correctly.
   - Adjust the distance thresholds in the code as needed based on your maze size and sensor placement.

## Circuit Diagram

```
Arduino Board:
5V → VCC of Ultrasonic Sensors
GND → GND of L298N, Ultrasonic Sensors, and External Power Supply

L298N Motor Driver:
VCC → External 12V Power Supply
GND → GND of External Power Supply and Arduino GND

Motor Connections (L298N):
Motor 1 (Left Motor):
  OUT1 → One terminal of Left Motor
  OUT2 → Other terminal of Left Motor
Motor 2 (Right Motor):
  OUT3 → One terminal of Right Motor
  OUT4 → Other terminal of Right Motor

Control Pins:
IN1 → Pin 3 of Arduino
IN2 → Pin 4 of Arduino
IN3 → Pin 5 of Arduino
IN4 → Pin 6 of Arduino

Ultrasonic Sensors:
Front Sensor:
  VCC → 5V of Arduino
  GND → GND of Arduino
  Trig → Pin 7 of Arduino
  Echo → Pin 8 of Arduino
Left Sensor:
  VCC → 5V of Arduino
  GND → GND of Arduino
  Trig → Pin 9 of Arduino
  Echo → Pin 10 of Arduino
Right Sensor:
  VCC → 5V of Arduino
  GND → GND of Arduino
  Trig → Pin 11 of Arduino
  Echo → Pin 12 of Arduino
```

## Arduino Code

```cpp
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
  int distance = duration * 0.0344 / 2; // Convert to cm

  return distance;
}

void updatePathMarkers(int distanceFront, int distanceLeft, int distanceRight) {
  const int obstacleThreshold = 10; // cm

  // Update path markers based on distance readings
  pathMarked[0] = (distanceFront <= obstacleThreshold); // Forward
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
```

## Contributing

We welcome contributions to the Zyroxin Robot project! If you have suggestions for improvements or bug fixes, please open an issue or submit a pull request.

## License

This project is open source and available under the [MIT License](LICENSE).
