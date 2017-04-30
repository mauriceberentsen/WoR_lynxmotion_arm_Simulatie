/*
 * VirtualController.cpp
 *
 *  Created on: Apr 30, 2017
 *      Author: Agit
 */

#include "VirtualController.hpp"
#include <regex>
#include <algorithm>
#include <math.h>

VirtualController::VirtualController():pub_(n_.advertise<robot_arm_simulatie_bp::Num>("input", 1000)),
									   sub_(n_.subscribe<std_msgs::String>("SSC_32U_messages", 1000,&VirtualController::parseMessage,this))
{
	joint_pos.data = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
}

VirtualController::~VirtualController()
{
}

void VirtualController::parseMessage(const std_msgs::String::ConstPtr& msg)
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
	else if(msg->data=="RESET")
	{
		joint_pos.data = joint_pos.data = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
		pub_.publish(joint_pos);
	}
	else
	{
		 ROS_INFO("Invalid message in function parseMessage");
	}
}

void VirtualController::multipleServoCommand(const std::string& command,
		bool spd, bool time)
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
					search_query+="#([[:digit:]]+)[[:space:]]*P([[:digit:]]+)[[:space:]]*S([[:digit:]]+)[[:space:]]*";
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

	    				if(pos_speed_temp == std::string::npos)
	    				{
	    				    search_query+="#([[:digit:]]+)[[:space:]]*P([[:digit:]]+)[[:space:]]*S([[:digit:]]+)[[:space:]]*";
	    				    ++n_speed;
	    				}
	    				else
	    				{
	    					search_query+="#([[:digit:]]+)[[:space:]]*P([[:digit:]]+)[[:space:]]*";
	    				}
	    			    ++n_pulse;
					}
					else
					{
						search_query+="#([[:digit:]]+)[[:space:]]*P([[:digit:]]+)[[:space:]]*";
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
			  ROS_INFO("I saw_MatchResults 5: [%s]", matchResults.str(5).c_str());
			  ROS_INFO("I saw_MatchResults 6: [%s]", matchResults.str(6).c_str());
			  ROS_INFO("I saw_MatchResults 7: [%s]", matchResults.str(7).c_str());
			  ROS_INFO("I saw_MatchResults 8: [%s]", matchResults.str(8).c_str());
			  ROS_INFO("I saw_MatchResults 9: [%s]", matchResults.str(9).c_str());
		  }
		  else
		  {
			  ROS_INFO("search_query was: [%s]", search_query.c_str());
			  ROS_INFO("Invalid input in function multiServoCommand");
		  }

}

void VirtualController::singleServoCommand(const std::string& command, bool spd,
		bool time)
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
		  long speed = -1;
		  long time  = -1;
		  ROS_INFO("I heard: [%s]", command.c_str());
		  ROS_INFO("I saw_MatchResults 0: [%s]", matchResults.str(0).c_str());
		  ROS_INFO("I saw_MatchResults 1: [%s]", matchResults.str(1).c_str());
		  ROS_INFO("I saw_MatchResults 2: [%s]", matchResults.str(2).c_str());
		  ROS_INFO("I saw_MatchResults 3: [%s]", matchResults.str(3).c_str());
		  ROS_INFO("I saw_MatchResults 4: [%s]", matchResults.str(4).c_str());

		  if(spd && time)
		  {
			 speed = stoul(matchResults.str(2));
			 time = stoul(matchResults.str(3));
		  }
		  else if(spd)
		  {
			  speed = stoul(matchResults.str(2));
		  }
		  else if(time)
		  {
			  time = stoul(matchResults.str(2));
		  }
		  pubJointStates(stoul(matchResults.str(1)),stoul(matchResults.str(2)),speed,time);
	  }
	  else
	  {
		  ROS_INFO("Invalid input in function singleServoCommand");
	  }
}


//restricties in graden staan in comentaar
//pin nummer aan gehouden volgens beroepsproduct 1 interface
void VirtualController::pubJointStates(std::size_t pin, std::size_t pwm,long speed, long time)
{
	robot_arm_simulatie_bp::Num temp_joint_pos = joint_pos;

	if(pin==0)
	{
		joint_pos.data.at(pin) = pwmToRadial(pwm,640,2360,-M_PI_2,M_PI_2); //-90 graden tot 90 graden base
	}
	else if(pin==1)
	{
		joint_pos.data.at(pin) = pwmToRadial(pwm,1800,800, M_PI_2/3	,-M_PI/3); //-30 graden tot 90 graden shoulder
	}
	else if(pin==2)
	{
		joint_pos.data.at(pin) = pwmToRadial(pwm,680,1920,0,(M_PI_2 + M_PI_4)); //0 graden tot 135 graden elbow
	}
	else if(pin==3)
	{
		joint_pos.data.at(pin) = pwmToRadial(pwm,630,2430,-M_PI_2,M_PI_2); //-90 graden tot 90 graden wrist
	}
	else if(pin==5)
	{
		joint_pos.data.at(pin-1) = pwmToRadial(pwm,700,2400,-M_PI_2,M_PI_2); //-90 graden tot 90 graden wrist rotate
	}
	else if(pin==4)
	{
		double gripper_state = pwmToRadial(pwm,850,2300,-0.02,0.02); //Full open, Full dicht values gripper
		joint_pos.data.at(pin+1) = gripper_state;
		joint_pos.data.at(pin+2) = gripper_state;
	}
	else
	{
		ROS_INFO("Invalid joint control request");
		return;
	}

	//ros::Rate loop_rate(10);
	//if(time)
	//{
		pub_.publish(joint_pos);
	//}
}

double VirtualController::pwmToRadial(std::size_t input_pwm,
		std::size_t min_pwm, std::size_t max_pwm,double min_rad, double max_rad)
{
	if(input_pwm>max_pwm)
	{
		input_pwm=max_pwm;
	}
	else if(input_pwm<min_pwm)
	{
		input_pwm=min_pwm;
	}
	return (input_pwm - min_pwm) * (max_rad - min_rad) / (max_pwm - min_pwm) + min_rad;
}
