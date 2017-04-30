/*
 * controller.cpp
 *
 *  Created on: Apr 27, 2017
 *      Author: Agit
 */

#include "ros/ros.h"
#include "VirtualController.hpp"
//Single Servo Commands
//# <ch> P <pw> ​S​​<spd>​​T​<time> <cr>
/*
 * ● <ch>: pin / channel to which the servo is connected (0 to 31) in decimal
● <pw>: desired pulse width (normally 500 to 2500) in microseconds
● <spd>: servo movement speed in microseconds per second*
● <time>: time in microseconds to travel from the current position to the desired position.
This affects all servos (65535 max) *
● <cr>: carriage return (ASCII 13)**
 */

//Example 1: #5P1500S750<cr>
//Example 2: #3 P1600 T1000 <cr>

//Multiple servo command (a.k.a. “Command Group”)
//# <ch> P <pw> S ​<spd>​... # <ch> P <pw> S ​<spd>​T <time> <cr>
//Example 1: #5 P1600 #10 P750 T2500 <cr>


int main(int argc, char **argv)
{
	ros::init(argc, argv, "controller");

	VirtualController controller;

	ros::spin();

	return 0;
}


