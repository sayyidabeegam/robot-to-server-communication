# Use the official ROS Noetic base image
FROM ros:noetic

# Install git
RUN apt-get update && apt-get install -y git

# Create a catkin workspace and clone the repository
RUN mkdir -p /catkin_ws/src
WORKDIR /catkin_ws/src
RUN git clone https://github.com/sayyidabeegam/robot-to-server-communication.git

# Build the catkin workspace
WORKDIR /catkin_ws
RUN /bin/bash -c "source /opt/ros/noetic/setup.bash && catkin_make"

# Source the setup.bash for the catkin workspace
RUN echo "source /catkin_ws/devel/setup.bash" >> /root/.bashrc

# Change to the source directory of the comm_tcp package and compile the C++ code
WORKDIR /catkin_ws/src/robot-to-server-communication/robot_to_server_comm/src
RUN g++ -o tcp_receiver tcp_receiver.cpp

# Set the default command to run bash
CMD ["/bin/bash"]

