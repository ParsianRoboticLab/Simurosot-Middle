#include "stdafx.h"
#include "../soccer.h"
#include "../util/bangbang.h"
#include "../util/pid.h"

void Soccer::spin(int id, const rcsc::Vector2D&  targetPos, const double &targetVel) {
	const rcsc::Vector2D& ballPos{ wm->getBall().pos };
	const rcsc::Ray2D& ballPath{ wm->getBall().pos, wm->getBall().vel };
	const rcsc::Vector2D& robotPos{ wm->ourRobot(id).pos };
	double angle{ rcsc::Vector2D::angleOf(robotPos, ballPos, targetPos).degree() };
	rcsc::Circle2D robotArea{ wm->ourRobot(id).pos, ROBOT_HALF_WIDTH*sqrt(2) };
	double vel_w{ (angle > 0) ? -40. : 40. };
	if (targetVel != -1)
		vel_w = (angle > 0) ? -targetVel : targetVel;
	setRobotVel(id, 1, vel_w);
}
