/*
 * joint_aansturing.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: Agit
 */

#include <robot_state_publisher/robot_state_publisher.h>

int main(int argc, char **argv)
{

	ros::init(argc, argv, "joint_controller");
	ros::NodeHandle n;

	//RobotStatePublisher(const KDL::Tree& tree);

	// publish moving joints
	//void publishTransforms(const std::map<std::string, double>& joint_positions,
	//                        const ros::Time& time);

	// publish fixed joints
	//void publishFixedTransforms();

	ROS_INFO("joint_controller");
	ros::spin();
	return 0;
}

