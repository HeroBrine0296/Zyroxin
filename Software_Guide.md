# Software Guide

## Prerequisites

1. **Arduino IDE**:
   - Download and install the Arduino IDE from the [official website](https://www.arduino.cc/en/software).

2. **Libraries**:
   - Ensure you have the necessary libraries installed for ultrasonic sensors and motor control. You can install them via the Arduino Library Manager.

## Code Setup

### 1. Download the Code

1. **Get the Code**:
   - Download the Arduino sketch from the `code/src/` directory of this repository.

### 2. Open and Configure the Code

1. **Open the Arduino IDE**:
   - Launch the Arduino IDE on your computer.

2. **Load the Sketch**:
   - Open the `MazeSolver.ino` file from the downloaded code.

3. **Select the Board and Port**:
   - Go to `Tools` -> `Board` and select `Arduino Uno`.
   - Go to `Tools` -> `Port` and select the port to which your Arduino is connected.

### 3. Upload the Code

1. **Verify and Upload**:
   - Click the **Verify** button to compile the code and ensure there are no errors.
   - Click the **Upload** button to upload the code to the Arduino.

### 4. Testing

1. **Power On the Robot**:
   - Connect the battery pack and turn on the robot.

2. **Run the Robot**:
   - Place the robot in a maze and observe its behavior. Ensure that the sensors and motors are functioning correctly.

## Troubleshooting

- **No Response from Motors**:
  - Check the connections to the L298N motor driver.
  - Verify that the motor driver is receiving power.

- **Inaccurate Obstacle Detection**:
  - Check the alignment and placement of the ultrasonic sensors.
  - Ensure there is no interference affecting sensor readings.

## Additional Resources

- For more detailed information on using the Arduino IDE, refer to the [Arduino Documentation](https://www.arduino.cc/en/Guide).
- For help with specific libraries, consult the library documentation available within the Arduino IDE or on their respective GitHub pages.
