#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "sensor_msgs/Imu.h"

#define dt 0.1

double my_angle = 0;

std_msgs::Float64 wheel1_vel;
std_msgs::Float64 wheel2_vel;
std_msgs::Float64 wheel3_vel;

void ang_velCallback(const sensor_msgs::Imu::ConstPtr& imu)
{
  my_angle = my_angle + imu->angular_velocity.z*dt;
  if(my_angle < 3.14)
  {
    wheel1_vel.data = -0.5;
    wheel2_vel.data = -0.5;
    wheel3_vel.data = -0.5;
  }
  else
  {
    wheel1_vel.data = 0;
    wheel2_vel.data = 0;
    wheel3_vel.data = 0;
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gyro_test");
  ros::NodeHandle n;
  
  ros::Publisher wheel1_vel_pub;
  ros::Publisher wheel2_vel_pub;
  ros::Publisher wheel3_vel_pub;

  ros::Subscriber ang_vel_sub;
  
  wheel1_vel_pub = n.advertise<std_msgs::Float64>("omnibot3/wheel1_controller/command", 1000);
  wheel2_vel_pub = n.advertise<std_msgs::Float64>("omnibot3/wheel2_controller/command", 1000);
  wheel3_vel_pub = n.advertise<std_msgs::Float64>("omnibot3/wheel3_controller/command", 1000);
  
  ang_vel_sub = n.subscribe("imu1", 1000, ang_velCallback);

  ros::Rate loop_rate(10);
  
  while(ros::ok())
  {
    wheel1_vel_pub.publish(wheel1_vel);
    wheel2_vel_pub.publish(wheel2_vel);
    wheel3_vel_pub.publish(wheel3_vel);

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
