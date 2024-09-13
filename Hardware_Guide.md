# Hardware Guide

## Components

- **Arduino Uno**: The microcontroller board that controls the robot.
- **3 x Ultrasonic Sensors**: Used for obstacle detection and distance measurement.
- **L298N Motor Driver**: Controls the direction and speed of the wheel motors.
- **2 x Wheel Motors**: Provide movement for the robot.
- **Battery Pack**: Provides power to the Arduino, sensors, and motors.
- **Various Connectors and Wires**: For making the necessary electrical connections.

## Assembly Instructions

### 1. Connecting the Ultrasonic Sensors

1. **Wiring**:
   - Connect the **VCC** pin of each ultrasonic sensor to the 5V pin on the Arduino.
   - Connect the **GND** pin of each ultrasonic sensor to the GND pin on the Arduino.
   - Connect the **Trig** and **Echo** pins of each sensor to designated digital pins on the Arduino (e.g., Trig1 to D2, Echo1 to D3, etc.).

2. **Placement**:
   - Mount the ultrasonic sensors on the front of the robot, spaced apart to cover a wide area.

### 2. Connecting the Motor Driver

1. **Wiring**:
   - Connect the **IN1**, **IN2**, **IN3**, and **IN4** pins of the L298N motor driver to the digital pins on the Arduino (e.g., IN1 to D8, IN2 to D9, etc.).
   - Connect the **OUT1** and **OUT2** terminals to the terminals of the left wheel motor.
   - Connect the **OUT3** and **OUT4** terminals to the terminals of the right wheel motor.
   - Connect the **VCC** and **GND** pins of the L298N to the battery pack.

2. **Power**:
   - Ensure that the motor driver is connected to a sufficient power source to drive the motors.

### 3. Powering the System

1. **Battery Pack**:
   - Connect the battery pack to the Arduino’s power input and the L298N motor driver.
   - Ensure the voltage matches the requirements of both the Arduino and motor driver.

2. **Double-Check Connections**:
   - Verify all connections are secure and correctly oriented.

## Circuit Diagram

Refer to the circuit diagram below for a visual representation of the connections.
xyz
![Circuit Diagram](xyz)
