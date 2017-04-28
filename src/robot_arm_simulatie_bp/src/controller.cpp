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

void parseMessage(const std_msgs::String::ConstPtr& msg)
{
  //std::regex e("([[:w:]]+)[[:space:]]+([[:w:]]+)");

	//  \#\d+\P\d+\S\d+
  //std::regex e("\#\d+\P\d+\S\d+");
  //std::regex e("\#\d+\P\d+\S\d+");
  std::regex e("#([[:digit:]]+)[[:space:]]*P([[:digit:]]+)[[:space:]]*S([[:digit:]]+)");
  std::smatch matchResults;

  if(std::regex_match(msg->data, matchResults, e))
  {
	  ROS_INFO("I heard: [%s]", msg->data.c_str());
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

 // ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "controller");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("SSC_32U_messages", 1000, parseMessage);

	ros::spin();

	return 0;
}


