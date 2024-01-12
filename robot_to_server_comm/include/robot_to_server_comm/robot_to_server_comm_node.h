#ifndef ROBOTSERVERCOMMNODE
#define ROBOTSERVERCOMMNODE

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <nav_msgs/Odometry.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class TcpSender {
public:
    TcpSender(const std::string& server_ip, int server_port);
    ~TcpSender();

    void sendData(const std::string& data);

protected:
    int sockfd_;
    struct sockaddr_in server_addr_;
};

class RobotToServerCommNode : public TcpSender {
public:
    RobotToServerCommNode(ros::NodeHandle& nh, const std::string& server_ip, int server_port);
    ~RobotToServerCommNode();

private:
    ros::Subscriber imu_sub_;
    ros::Subscriber odom_sub_;

    void imuCallback(const sensor_msgs::Imu::ConstPtr& imu_msg);
    void odomCallback(const nav_msgs::Odometry::ConstPtr& odom_msg);
};

#endif // ROBOTSERVERCOMMNODE
