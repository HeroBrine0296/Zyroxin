# Zyroxin Maze Solver

Zyroxin is an open-source robot designed to autonomously solve mazes. It utilizes 3 ultrasonic sensors, an L298N motor driver, an Arduino Uno, and 2 wheel motors to navigate through the maze.

## Features

- Maze navigation using 3 ultrasonic sensors
- Motor control through L298N driver
- Simple maze-solving algorithm implemented on Arduino Uno

## Getting Started

Follow these steps to set up Zyroxin:

### 1. Assemble the Hardware

1. **Connect the Ultrasonic Sensors**: Connect each ultrasonic sensor to the Arduino Uno as shown in the wiring diagram below.
2. **Connect the Motor Driver**: Connect the L298N motor driver to the Arduino and the wheel motors.
3. **Power Supply**: Ensure that all components are properly powered.

### 2. Install the Software

1. **Install the Arduino IDE**: Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
2. **Upload the Code**: Download the code from the `code/src/` folder and upload it to the Arduino Uno.

### 3. Run the Robot

1. **Power On**: Turn on the robot and ensure it is placed in a maze environment.
2. **Observe**: The robot will start navigating the maze using its sensors and motor driver.

## Code

The code for Zyroxin is located in the `code/src/` directory.

- `MazeSolver.ino`: Arduino code for the maze-solving algorithm.

## Hardware Guide

- **Components**: 
  - 1 x Arduino Uno
  - 3 x Ultrasonic Sensors
  - 1 x L298N Motor Driver
  - 2 x Wheel Motors
  - Various connectors and cables

- **Circuit Diagram**: [Zyroxin Circuit Diagram](hardware/Zyroxin_Circuit.pdf)
- **Parts List**: See [Parts List](hardware/Parts_List.md) for detailed information.

## Media

- **Demo**: ![Demo](media/zyroxin_demo.gif)
- **Images**:
  - ![Robot Image](media/images/Zyroxin_Robot.jpg)
  - ![Wiring Diagram](media/images/Wiring_Diagram.png)

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch for your changes.
3. Submit a pull request with a detailed description of your changes.

## Contact

For any questions or feedback, please contact [Shafquat](mailto:shafquatk51@gmail.com).

