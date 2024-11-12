# CarCarC 🚗💨

CarCarC is a smart, responsive waste collection system designed to make trash disposal more convenient and efficient in public spaces. With innovative sensors and automated features, CarCarC can navigate to designated locations, avoid obstacles, and interact with users seamlessly.

## Project Overview

This project integrates multiple technologies to create an interactive, mobile waste collection system. Key features include an IoT-based trash bin that can be summoned on demand, autonomous navigation using ESP32 and PSoC, and a responsive interface for real-time interactions. This system aims to reduce the workload for waste management and enhance the user experience.

## Features

### 1. On-Demand Summoning 🚨
- **AWS API Gateway Integration**: Users can summon CarCarC using an AWS API-powered interface.
- **ESP32 and Serverless Framework**: Facilitates secure communication between user commands and the waste collection unit.

### 2. Autonomous Navigation 🚗
- **ESP32 and Arduino MEGA**: Coordinate to control the movement and navigate to specific locations.
- **Obstacle Detection**: Uses ultrasonic sensors (HCSR04) to identify obstacles and adjust the route as necessary.

### 3. User Interaction and Notifications 📲
- **Interactive Display**: A PSoC-based screen shows environmental data and provides notifications.
- **Automatic Trash Bin Lid**: The lid opens when sensors detect a user nearby, improving accessibility and hygiene.

### 4. Smart Features 🧠
- **RFID Positioning**: Assists in navigation by pinpointing specific locations.
- **Ultrasonic Sensors**: Detect obstacles and provide feedback to adjust the vehicle’s path.
- **Ambient Light Sensor**: Triggers automated responses, such as opening the lid in low light for improved usability.

## System Architecture

The CarCarC system is divided into four major components:

1. **User Summoning**: User interface with AWS and ESP32, using a serverless framework to initiate commands.
2. **Internal Communication**: Data exchange between ESP32, Arduino MEGA, and other subsystems to manage navigation.
3. **User Interaction Module**: Sensor and display system that responds to environmental stimuli and user presence.
4. **Smart Trash Bin Features**: RFID and ultrasonic sensors for positioning and obstacle avoidance, with automated functions for user convenience.

## Power Supply

- 9V battery and mobile power sources.
- USB-powered ESP32 and other components.

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/Alanhsiu/CarCarC.git
   ```
2. Set up the AWS API Gateway and Serverless Framework as per the instructions provided in docs/api-setup.md.
3. Flash the ESP32 and Arduino MEGA firmware from the firmware directory.

## Future Expansion
CarCarC has potential applications in other automated service environments, such as ferry stations and airports, where reducing human contact and streamlining waste disposal are beneficial.