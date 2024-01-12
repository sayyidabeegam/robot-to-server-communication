#include "robot_to_server_comm/robot_to_server_comm_node.h"
#include <sstream>

TcpSender::TcpSender(const std::string& server_ip, int server_port) {
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ == -1) {
        perror("Error creating socket...");
        exit(EXIT_FAILURE);
    }

    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = htons(server_port);
    inet_pton(AF_INET, server_ip.c_str(), &server_addr_.sin_addr);

    if (connect(sockfd_, (struct sockaddr*)&server_addr_, sizeof(server_addr_)) == -1) {
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }
}

TcpSender::~TcpSender() {
    close(sockfd_);
}

void TcpSender::sendData(const std::string& data) {
    send(sockfd_, data.c_str(), data.size(), 0);
}

RobotToServerCommNode::RobotToServerCommNode(ros::NodeHandle& nh, const std::string& server_ip, int server_port)
    : TcpSender(server_ip, server_port) {
    imu_sub_ = nh.subscribe("/imu/data", 10, &RobotToServerCommNode::imuCallback, this);
    odom_sub_ = nh.subscribe("/navsat/odom", 10, &RobotToServerCommNode::odomCallback, this);
}

RobotToServerCommNode::~RobotToServerCommNode() {
}

void RobotToServerCommNode::imuCallback(const sensor_msgs::Imu::ConstPtr& imu_msg) {
    // Convert IMU data to a string packet
    std::stringstream ss;
    ss << "IMU Data: " << imu_msg->angular_velocity.x << " "
                      << imu_msg->angular_velocity.y << " "
                      << imu_msg->angular_velocity.z;
    
    // Send the data using TcpSender
    sendData(ss.str());
}

void RobotToServerCommNode::odomCallback(const nav_msgs::Odometry::ConstPtr& odom_msg) {
    // Convert Odometry data to a string packet
    std::stringstream ss;
    ss << "Odom Data: " << odom_msg->pose.pose.position.x << " "
                       << odom_msg->pose.pose.position.y << " "
                       << odom_msg->pose.pose.position.z;
    
    // Send the data using TcpSender
    sendData(ss.str());
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "my_node");
    ros::NodeHandle nh;

    // Instantiate the RobotToServerCommNode class
    RobotToServerCommNode my_node(nh, "127.0.0.1", 5000);

    // Spin the ROS event loop
    ros::spin();

    return 0;
}
