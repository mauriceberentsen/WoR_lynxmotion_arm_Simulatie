/*
 * joint_aansturing.cpp
 *
 *  Created on: Apr 24, 2017
 *      Author: Agit
 */

#include <robot_state_publisher/robot_state_publisher.h>
#include <sensor_msgs/JointState.h>

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
	ros::Rate loop_rate(10);

	int count = 0;
	while (ros::ok())
	{

		sensor_msgs::JointState joint_state;

		joint_state.header.stamp.sec=count;
		joint_state.name = {"base_link2turret", "turret2upperarm", "upperarm2forearm", "forearm2wrist", "wrist2hand", "gripper_left2hand", "gripper_right2hand"};
		joint_state.position = {0.0, 0.0, 0.0, 0.0, float((count % 2)), 0.0, 0.0};

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

		loop_rate.sleep();
		++count;
	}
	//ROS_INFO("joint_controller");
	//ros::spin();
	return 0;
}

