#include "ros/ros.h"
#include "std_msgs/Float64.h"

#include <cmath>

#define MAX_SPEED 3
#define STEP 0.1

int main(int argc, char **argv)
{
  ros::init(argc, argv, "drive_test");
  ros::NodeHandle n;

  ros::Publisher wheel1_vel_pub = n.advertise<std_msgs::Float64>("omnibot3/wheel1_controller/command", 1000);
  ros::Publisher wheel2_vel_pub = n.advertise<std_msgs::Float64>("omnibot3/wheel2_controller/command", 1000);
  ros::Publisher wheel3_vel_pub = n.advertise<std_msgs::Float64>("omnibot3/wheel3_controller/command", 1000);
  
  ros::Rate loop_rate(10);
  
  int count = 0;
  while(ros::ok())
  {
    std_msgs::Float64 wheel1_vel;
    std_msgs::Float64 wheel2_vel;
    std_msgs::Float64 wheel3_vel;
    
    // set each velocity (rad/s)
    wheel1_vel.data = MAX_SPEED * sin(count * STEP);
    wheel2_vel.data = 0;
    wheel3_vel.data = -1 * MAX_SPEED * sin(count * STEP);

    wheel1_vel_pub.publish(wheel1_vel);
    wheel2_vel_pub.publish(wheel2_vel);
    wheel3_vel_pub.publish(wheel3_vel);

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }

  return 0;
}
