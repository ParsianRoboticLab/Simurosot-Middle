#include "stdafx.h"
#include "../soccer.h"

void Soccer::Goalie(int id) {
	double y = wm->getBall().pos.y + wm->getBall().vel.y;
	if (y < -Field::goalWidth / 2) y = -Field::goalWidth / 2;
	if (y > Field::goalWidth / 2) y = Field::goalWidth / 2;

	rcsc::Vector2D targetVel = rcsc::Vector2D(0, 1000);
	rcsc::Vector2D targetPos = rcsc::Vector2D(-Field::width / 2 + 5, y);
	double pathdist = wm->ourRobot(id).pos.dist(targetPos);
	double pathTh = -(targetPos - wm->ourRobot(id).pos).th().degree();
	double angle{ fabs(wm->ourRobot(id).th - pathTh) };
	if (angle > 180)
		angle -= 360;
	if (angle < -180)
		angle += 360;
	angle = fabs(angle);
	if (pathdist < 5) {
		setRobotAng(id, targetVel.th().degree());
	}
	if (angle <= 15)
	{
		setRobotVel(id, pathdist*0.3, 0);
	}
	else if (angle >= 165 && angle <= 180) {
		setRobotVel(id, -fabs(pathdist*0.3), 0);
	}
	else if (angle > 15 && angle <= 90) {
		setRobotAng(id, pathTh);
	}
	else if (angle > 90 && angle < 165) {
		setRobotAng(id, 180 + pathTh);
	}
}