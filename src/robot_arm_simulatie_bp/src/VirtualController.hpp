/*
 * VirtualController.hpp
 *
 *  Created on: Apr 30, 2017
 *      Author: Agit
 */

#ifndef SRC_ROBOT_ARM_SIMULATIE_BP_SRC_VIRTUALCONTROLLER_HPP_
#define SRC_ROBOT_ARM_SIMULATIE_BP_SRC_VIRTUALCONTROLLER_HPP_
#include "std_msgs/String.h"
#include "ros/ros.h"
#include "robot_arm_simulatie_bp/Num.h"
class VirtualController
{
public:
	VirtualController();
	virtual ~VirtualController();

private:
  void parseMessage(const std_msgs::String::ConstPtr& msg);

  //Multiple servo command (a.k.a. “Command Group”)
  void multipleServoCommand(const std::string& command,bool spd, bool time);

  //Single Servo Commands
  void singleServoCommand(const std::string& command,bool spd,bool time);

  void pubJointStates(std::size_t pin, std::size_t pwm,long speed, long time);

  double pwmToRadial(std::size_t input_pwm, std::size_t min_pwm, std::size_t max_pwm,double min_rad, double max_rad);

  ros::NodeHandle n_;
  ros::Publisher pub_;
  ros::Subscriber sub_;
  robot_arm_simulatie_bp::Num joint_pos;
};

#endif /* SRC_ROBOT_ARM_SIMULATIE_BP_SRC_VIRTUALCONTROLLER_HPP_ */
