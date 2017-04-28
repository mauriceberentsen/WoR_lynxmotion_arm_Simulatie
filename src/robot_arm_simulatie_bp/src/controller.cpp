/*
 * controller.cpp
 *
 *  Created on: Apr 27, 2017
 *      Author: Agit
 */

#include "ros/ros.h"
#include "std_msgs/String.h"
#include <regex>
#include <algorithm>
#include <iostream>

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


//Single Servo Commands
void singleServoCommand(const std::string& command,bool spd,bool time)
{
	  std::regex e;

	  if(spd && time)
	  {
		 e = "#([[:digit:]]+)[[:space:]]*P([[:digit:]]+)[[:space:]]*S([[:digit:]]+)[[:space:]]*T([[:digit:]]+)";
	  }
	  else if(spd)
	  {
		 e = "#([[:digit:]]+)[[:space:]]*P([[:digit:]]+)[[:space:]]*S([[:digit:]]+)";
	  }
	  else if(time)
	  {
		 e = "#([[:digit:]]+)[[:space:]]*P([[:digit:]]+)[[:space:]]*T([[:digit:]]+)";
	  }
	  else
	  {
		 e = "#([[:digit:]]+)[[:space:]]*P([[:digit:]]+)[[:space:]]*";
	  }

	  std::smatch matchResults;

	  if(std::regex_match(command, matchResults, e))
	  {
		  ROS_INFO("I heard: [%s]", command.c_str());
		  ROS_INFO("I saw_MatchResults 0: [%s]", matchResults.str(0).c_str());
		  ROS_INFO("I saw_MatchResults 1: [%s]", matchResults.str(1).c_str());
		  ROS_INFO("I saw_MatchResults 2: [%s]", matchResults.str(2).c_str());
		  ROS_INFO("I saw_MatchResults 3: [%s]", matchResults.str(3).c_str());
		  ROS_INFO("I saw_MatchResults 4: [%s]", matchResults.str(4).c_str());
	  }
	  else
	  {
		  ROS_INFO("Invalid input");
	  }
}

//Multiple servo command (a.k.a. “Command Group”)
void multipleServoCommand(const std::string& command,bool spd, bool time)
{
	  std::regex e;
	  std::string search_query="";
	  std::size_t n_servo = std::count(command.begin(),command.end(),'P');

	  if(spd)
	  {
		 std::size_t n_spd = std::count(command.begin(),command.end(),'S');

		 if(n_servo == n_spd)
		 {
			 for(std::size_t i = 0; i<n_servo; ++i)
			 {
				search_query+="#([[:digit:]]+)[[:space:]]*P([[:digit:]]+[[:space:]]*S([[:digit:]]+))[[:space:]]*";
			 }
			 search_query+="T([[:digit:]]+)";
			 e = search_query;
		 }
		 else
		 {
			 std::size_t n_pulse = 0;
			 std::size_t n_speed = 0;
			 for(std::size_t i = 0; i<n_servo; ++i)
			 {
				n_pulse = command.find('P',n_pulse);
				n_speed = command.find('S',n_speed);

				if(n_speed != std::string::npos)
				{
					std::string temp = command.substr(n_pulse,(n_speed-n_pulse));
					std::size_t pos_speed_temp= temp.find('#');

    				if(pos_speed_temp ==std::string::npos)
    				{
    				    std::cout<<i<<std::endl;
    				    search_query+="#([[:digit:]]+)[[:space:]]*P([[:digit:]]+[[:space:]]*S([[:digit:]]+))[[:space:]]*";
    				    ++n_speed;
    				}
    				search_query+="#([[:digit:]]+)[[:space:]]*P([[:digit:]]+[[:space:]]*";
    			    ++n_pulse;
				}
				else
				{
					search_query+="#([[:digit:]]+)[[:space:]]*P([[:digit:]]+[[:space:]]*";
				}
			 }
			 search_query+="T([[:digit:]]+)";
			 e = search_query;
		 }
	  }
	  else if(time)
	  {
		 for(std::size_t i = 0; i<n_servo; ++i)
		 {
			 search_query+="#([[:digit:]]+)[[:space:]]*P([[:digit:]]+)[[:space:]]*";
		 }
		 search_query+="T([[:digit:]]+)";
		 e = search_query;
	  }
	  else
	  {
		 ROS_INFO("Invalid message");
		 return;
	  }

	  std::smatch matchResults;
	  if(std::regex_match(command, matchResults, e))
	  {
		  ROS_INFO("I heard: [%s]", command.c_str());
		  ROS_INFO("I saw_MatchResults 0: [%s]", matchResults.str(0).c_str());
		  ROS_INFO("I saw_MatchResults 1: [%s]", matchResults.str(1).c_str());
		  ROS_INFO("I saw_MatchResults 2: [%s]", matchResults.str(2).c_str());
		  ROS_INFO("I saw_MatchResults 3: [%s]", matchResults.str(3).c_str());
		  ROS_INFO("I saw_MatchResults 4: [%s]", matchResults.str(4).c_str());
	  }
	  else
	  {
		  ROS_INFO("Invalid input");
	  }

}
void parseMessage(const std_msgs::String::ConstPtr& msg)
{
	std::size_t n_pulse = std::count(msg->data.begin(),msg->data.end(),'P');
	bool time  = std::count(msg->data.begin(),msg->data.end(),'T') > 0;
	bool speed = std::count(msg->data.begin(),msg->data.end(),'S') > 0;

	if(n_pulse>1)
	{
		multipleServoCommand(msg->data,speed,time);
	}
	else if(n_pulse==1)
	{
		singleServoCommand(msg->data,speed,time);
	}
	else
	{
		 ROS_INFO("Invalid message");
	}
}


int main(int argc, char **argv)
{
	ros::init(argc, argv, "controller");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("SSC_32U_messages", 1000, parseMessage);

	ros::spin();

	return 0;
}


