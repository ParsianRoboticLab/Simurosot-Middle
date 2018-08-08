#include "stdafx.h"
#include "../soccer.h"

void Soccer::Goalie(int id) {
	rcsc::Segment2D ballPath{ wm->getBall().pos, wm->getBall().vel.normalizedVector()*1000 };
	rcsc::Segment2D goalLine{ Field::ourGoalB(), Field::ourGoalT() };
	rcsc::Vector2D p;
	p = ballPath.intersection(goalLine, true);
	if (wm->getBall().vel.length() < 0.5) p.invalidate();
	double y;
	if (p.isValid()) {
		y = p.y;
	}
	else {
		LOG("BV: " << wm->getBall().vel.length());
		y = wm->getBall().pos.y + wm->getBall().vel.y*1;
	}


	if (y < -Field::goalWidth / 2 + 5) y = -Field::goalWidth / 2 + 2;
	if (y > Field::goalWidth / 2 - 5) y = Field::goalWidth / 2 - 2;

	rcsc::Vector2D targetVel = rcsc::Vector2D(0, 1000);
	rcsc::Vector2D targetPos = rcsc::Vector2D(-Field::width / 2 + 2, y);
	if (wm->ourRobot(id).pos.x > -Field::width / 2 + 5) targetPos = Field::ourGoal();
	double pathdist = wm->ourRobot(id).pos.dist(targetPos);
	double pathTh = -(targetPos - wm->ourRobot(id).pos).th().degree();
	double angle{ fabs(wm->ourRobot(id).th - pathTh) };
	if (angle > 180)
		angle -= 360;
	if (angle < -180)
		angle += 360;
	angle = fabs(angle);
	if (pathdist < 2) {
		if (angle < 90) pathTh = 90;
		else pathTh = -90;
	}
	if (angle <= 2)
	{
		setRobotVel(id, pathdist*0.3, 0);
	}
	else if (angle >= 178 && angle <= 180) {
		setRobotVel(id, -fabs(pathdist*0.3), 0);
	}
	else if (angle > 2 && angle <= 90) {
		setRobotAng(id, pathTh);
	}
	else if (angle > 90 && angle < 178) {
		setRobotAng(id, 180 + pathTh);
	}

	// SPIN
	if (wm->getBall().pos.dist(wm->ourRobot(id).pos) < 8.5) {
		LOG("SPIN GOALIE");
		if (wm->getBall().pos.y > 0) setRobotVel(id, 0, 30);
		else setRobotVel(id, 0, -30);
	}

}