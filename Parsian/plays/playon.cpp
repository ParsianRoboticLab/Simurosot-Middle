#include "stdafx.h"
#include "../soccer.h"

void setRobotVel(double w, double vel_tan, double& right_wheel, double& left_wheel);

void Soccer::playon() {

	if (env->currentBall.pos.x > 10) ballInOurSide = false;
	else if (env->currentBall.pos.x < 10) ballInOurSide = true;

	//robot 1
	double right_wheel{};
	double left_wheel{};
	setRobotVel(0, 3.5, right_wheel, left_wheel);
	robots[1].velocityRight = right_wheel;
	robots[1].velocityLeft = left_wheel;

//	Goalie(env);
	Position(&robots[2], 0, 0);
	//Position(&robots[1], -50, -50);
	Position(&robots[3], -50, -50);
	Position(&robots[4], -50, -50);

}

void setRobotVel(double w, double vel_tan, double& right_wheel, double& left_wheel)
{
	//solve vel_tan
	//wheel =  a*x + b
	double a{ 2.7780205692975557e+001 }, b{ -3.3420738280453293e+000 };
	double right_vel_tan{ b + a * fabs(vel_tan) };
	double left_vel_tan{ b + a * fabs(vel_tan) };
	if (vel_tan < 0)
	{
		right_vel_tan *= -1;
		left_vel_tan *= -1;
	}
	//solve w
	//wheel = a*w + b
	double a1{ 1.86 }, b1{ 0.34 };
	double right_vel_w{ a1*fabs(w) + b1 };
	double left_vel_w{ a1*fabs(w) + b1 };
	if (w < 0)
	{
		right_vel_w *= -1;
		left_vel_w *= -1;
	}
	right_wheel = right_vel_tan + right_vel_w;
	left_wheel = left_vel_tan + left_vel_w;

}