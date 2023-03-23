# Capstone-Boance
Repository for the University of Turku Capstone Project

# Automatic Boat Posture Correction System
This project aims to develop a system that automatically corrects the posture of a boat using sensors and advanced algorithms, ensuring that the boat stays on course even in adverse weather conditions.

## Table of Contents
* [Introduction](#Introduction)
* [Features](#Features)
* [Requirements](#Requirements)
* [Installation](#Installation)
* [Usage](#Usage)
* [Media](#Media)
* [License](#License)

## Introduction
Boating can be a lot of fun, but it also requires skill and experience to navigate safely. One of the biggest challenges for boaters is staying on course, especially when wind and waves are strong. This projects aims to solve that problem by developing a system that uses sensors to automatically correct the boat's posture and keep it on course.

We created an Automatic Boat Posture Correction table top prototype which allows users to simulate the behavior of an automatic boat posture correction system in different weather conditions and navigation scenarios. This simulator can be used for testing and validating the performance of the system before deploying it in a real-world environment.

## Features
* Automatic boat posture correction using sensors.
* Support for multiple sensors.
* Customizable settings for different weather conditions and types of boats.
* Integration with other navigation and communication systems.

## Requirements
* Arduino Uno
* IMU sensor (Inertial Measurement Unit)
* Bread Board
* Servo motors
* Jumpers
* PlatformIO IDE

## Installation
1. Download the repository.
2. Install PlatformIO IDE extension on your Visual Studio Code.
3. Connect the IMU sensor and servo motor controllers to the Arduino Uno according to the specifications of the system.
4. Upload the code provided in this repository to the Arduino Uno through PlatformIO. 
5. Test the system to see that the servo motors actuate the appropriate motor blade when the sensor is tilted.

## Usage
The system is designed to automatically correct the posture of the boat based on the tilt detected by the IMU sensor. The system will adjust the servo motor blade serving as trim tabs as needed to reduce the rolling and pitching of the boat. 

## License
This project is licensed under the [MIT License](https://choosealicense.com/licenses/mit/). 

## Media
![Team Boance Promo Video](https://user-images.githubusercontent.com/40091471/227297075-f2c7bc11-0fd6-476c-bf3a-d2a75c97193a.gif)

![Team Boance Poster](https://github.com/BowenTT/Capstone-Boance/blob/main/Poster.jpg?raw=true)


