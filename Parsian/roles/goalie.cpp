#include "stdafx.h"
#include "../soccer.h"

void Soccer::Goalie(int id) {
	rcsc::Vector2D ballPos{wm->getBall().pos + wm->getBall().vel*5};
	rcsc::Line2D ballPath{ wm->getBall().pos, wm->getBall().pos + wm->getBall().vel.normalizedVector()*1000 };
	rcsc::Line2D goalLine{ Field::ourGoalB(), Field::ourGoalT() };
	rcsc::Vector2D p;
	p = ballPath.intersection(goalLine);
	if (wm->getBall().vel.length() < 0.5) p.invalidate();
	else if (ballPos.x < -100 && ballPos.y > Field::goalWidth/2) p.invalidate();
	else if (ballPos.x < -100 && ballPos.y < -Field::goalWidth / 2) p.invalidate();
	else if (ballPos.x > 45) p.invalidate();
	double y;
	bool forward{false};
	if (Field::ourPenaltyBRect().contains(ballPos) && wm->getBall().vel.length() < 1.5)
		forward = true;
	p.invalidate();
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
	if (pathdist < 2) {
		if (angle < 90) pathTh = 90;
		else pathTh = -90;
	}
	if (!forward)
	{
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
	else
	{
		kick(id, Field::oppGoal());
	}

	// SPIN
	if (wm->getBall().pos.dist(wm->ourRobot(id).pos) < 8.5 && wm->getBall().vel.length() < 2) {
		LOG("SPIN GOALIE");
		double spinnSpid{ 30 };
		#ifndef YELLOW
		spinnSpid *= -1;
		#endif // !YELLOW
		if (wm->getBall().pos.y > 0) setRobotVel(id, 0, spinnSpid);
		else setRobotVel(id, 0, -spinnSpid);
	}

}