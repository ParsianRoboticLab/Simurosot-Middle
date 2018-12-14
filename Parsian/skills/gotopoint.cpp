#include "stdafx.h"
#include "../soccer.h"
#include "../util/bangbang.h"
#include "../util/pid.h"

void Soccer::gotoPoint(int id, const rcsc::Vector2D&  targetPos, const rcsc::Vector2D& targetVel, double kp) {
	double pathdist = wm->ourRobot(id).pos.dist(targetPos);
	double pathTh = -(targetPos - wm->ourRobot(id).pos).th().degree();
	#ifndef YELLOW
	pathTh *= -1;
	#endif // !YELLOW
	double angle{ fabs(wm->ourRobot(id).th - pathTh) };
	#ifndef YELLOW
	angle = 180 - angle;
	#endif // !YELLOW
	if (angle > 180)
		angle -= 360;
	if (angle < -180)
		angle += 360;
	angle = fabs(angle);
	if (pathdist < 3) {
		if (pathdist < 2) {
			if (angle < 90) pathTh = targetVel.th().degree();
			else pathTh = -targetVel.th().degree();
		}
		
	}
	if (angle <= 15)
	{
		setRobotVel(id, pathdist*kp, 0);
	}
	else if (angle >= 165 && angle <= 180) {
		setRobotVel(id, -pathdist*kp, 0);
	}
	else if (angle > 15 && angle <= 90) {
		setRobotAng(id, pathTh);
	}
	else if (angle > 90 && angle < 165) {
		setRobotAng(id, 180 + pathTh);
	}

}