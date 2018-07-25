#include "stdafx.h"
#include "../soccer.h"
#include "../util/bangbang.h"
#include "../util/pid.h"

void Soccer::gotoPoint(int id, const rcsc::Vector2D&  targetPos, const rcsc::Vector2D& targetVel) {
	double dist = wm->ourRobot(id).pos.dist(targetPos);
	double pathTh = -(targetPos - wm->ourRobot(id).pos).th().degree();
	if (dist < 3) {
		setRobotAng(id, targetVel.th().degree());
	}
	else if (fabs(wm->ourRobot(id).th - pathTh) > 15) {
		setRobotAng(id, pathTh);
	}
	else {
		setRobotVel(id, dist*0.2, 0);
	}

}