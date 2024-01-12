# robot_to_server_comm

## Table of Contents

- [Overview](#overview)
- [Project design](#design)
- [Notes](#notes)
- [Usage](#usage)
- [Output](#output)
- [Contact](#contact)

## Overview

The "robot_to_server_comm" ROS package is designed to communicate different sensor data from the robot to the Mision Planner Server

## Project design 
### Repo overview
![repo](https://github.com/sayyidabeegam/robot-to-server-communication/assets/47295006/cc03f8de-71e1-4b67-97da-c011a9381154)

### Codebase design for robot_to_server_node
#### 1. Separation of Concerns:
The code follows a basic separation of concerns by having two classes: TcpSender for handling TCP communication, and RobotToServerCommNode as the main ROS node that inherits from TcpSender.
#### 2. Error Handling:
Error handling is implemented using perror 
#### 3. Subscriber Callbacks:
The subscriber callbacks (imuCallback and odomCallback) are straightforward, converting sensor data to string packets and sending them using TcpSender
## Notes
- The code is tested on Ubuntu 20.04.6 LTS
- ROS bag used for testing is [Dataset HK-Data20190117](https://github.com/weisongwen/UrbanLoco)
## Usage
### Build in native
```
$ source /opt/ros/<your ros version>/setup.bash
$ cd <your_ws>/src
$ git clone <this repo>
$ cd ...
$ catkin_make
$ source devel/setup.bash
```
### Testing
Terminal 1 - Start the roscore
```
$ roscore
```
Terminal 2 - Build and run tcp_receiver
```
$ g++ -o tcp_receiver tcp_receiver.cpp
$ ./tcp_receiver 
```
Terminal 3 - Run the rosbag
```
$ rosbag play test2.bag 
```
Terminal 4 - Run robot_to_server_node
```
$ cd <Your_ws>
$ source devel/setup.bash
$ roslaunch robot_to_server_comm robot_to_server.launch 
```

### Using docker file

## Output
Video
## Contact
Email: sayyidabeegam@gmail.com
