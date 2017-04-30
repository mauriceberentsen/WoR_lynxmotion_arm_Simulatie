/*
 * joint_aansturing.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: Agit
 */

#include <robot_state_publisher/robot_state_publisher.h>
#include <sensor_msgs/JointState.h>
//#include <std_msgs/Float64MultiArray.h>
//#include <std_msgs/Int32MultiArray.h>
#include "robot_arm_simulatie_bp/Num.h"

float g_base_link2turret=0;
float g_turret2upperarm=0;
float g_upperarm2forearm=0;
float g_forearm2wrist=0;
float g_wrist2hand=0;
float g_gripper_left2hand=0;
float g_gripper_right2hand=0;

void callBack(robot_arm_simulatie_bp::Num input)
{
	  ROS_INFO("input [%f]",g_base_link2turret=input.data.at(0));
	  ROS_INFO("input [%f]",g_turret2upperarm=input.data.at(1));
	  ROS_INFO("input [%f]",g_upperarm2forearm=input.data.at(2));
	  ROS_INFO("input [%f]",g_forearm2wrist=input.data.at(3));
	  ROS_INFO("input [%f]",g_wrist2hand=input.data.at(4));
	  ROS_INFO("input [%f]",g_gripper_left2hand=input.data.at(5));
	  ROS_INFO("input [%f]",g_gripper_right2hand=input.data.at(6));
}
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

	ros::Publisher joint_states_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1000);
	ros::Subscriber sub = n.subscribe<robot_arm_simulatie_bp::Num>("input", 1000,callBack);
	ros::Rate loop_rate(10);

	std::size_t count = 0;
	while (ros::ok())
	{

		sensor_msgs::JointState joint_state;

		joint_state.header.stamp.sec=count;
		joint_state.name = {"base_link2turret", "turret2upperarm", "upperarm2forearm", "forearm2wrist", "wrist2hand", "gripper_left2hand", "gripper_right2hand"};
		joint_state.position = {g_base_link2turret, g_turret2upperarm, g_upperarm2forearm, g_forearm2wrist, g_wrist2hand, g_gripper_left2hand, g_gripper_right2hand};

		/*header:
		  seq: 173
		  stamp:
		    secs: 1493465499
		    nsecs: 668412923
		  frame_id: ''
		name: ['base_link2turret', 'turret2upperarm', 'upperarm2forearm', 'forearm2wrist', 'wrist2hand', 'gripper_left2hand', 'gripper_right2hand']
		position: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
		velocity: []
		effort: []*/

		joint_states_pub.publish(joint_state);

		ros::spinOnce();
//
		loop_rate.sleep();
		++count;
	}
	//ROS_INFO("joint_controller");
	//ros::spin();
	return 0;
}

