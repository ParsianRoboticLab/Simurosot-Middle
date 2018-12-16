#include "stdafx.h"
#include "../soccer.h"
#include "../util/pid.h"

void Soccer::kick(int id, const rcsc::Vector2D&  targetPos) {

	rcsc::Vector2D ballPos{ wm->getBall().pos + wm->getBall().vel*(15. / 5.) };
	rcsc::Vector2D robotPos{ wm->ourRobot(id).pos + wm->ourRobot(id).vel*(5. / 5.) };
	rcsc::Vector2D norm{ ballPos - targetPos };
	norm = norm.normalize();
	rcsc::Vector2D prependicular{ norm.rotatedVector(90) };
	rcsc::Vector2D behindPos{ ballPos + norm * 20 };
	rcsc::Vector2D avoidPos{ ballPos + prependicular * 20 };
	rcsc::Circle2D robotArea{ robotPos, ROBOT_HALF_WIDTH*sqrt(2) };
	rcsc::Vector2D sol1, sol2;
	if (robotArea.intersection(rcsc::Ray2D{ ballPos, targetPos }, &sol1, &sol2) > 0)
	{
		if (avoidPos.x < -Field::width / 2 + ROBOT_WIDTH || avoidPos.x > Field::width / 2 + ROBOT_WIDTH || avoidPos.y < -Field::height / 2 + ROBOT_WIDTH || avoidPos.x > Field::height / 2 + ROBOT_WIDTH)
			avoidPos = ballPos;
		gotoPoint(id, avoidPos, behindPos, 0.3);
	}
	else if (wm->ourRobot(id).pos.dist(behindPos) > 25)
	{
		if (avoidPos.x < -Field::width / 2 + ROBOT_WIDTH || avoidPos.x > Field::width / 2 + ROBOT_WIDTH || avoidPos.y < -Field::height / 2 + ROBOT_WIDTH || avoidPos.x > Field::height / 2 + ROBOT_WIDTH)
			behindPos = ballPos;
		gotoPoint(id, behindPos, targetPos, 0.3);
	}
	else {
		gotoPoint(id, ballPos, targetPos, 0.3);
	}
	if (Field::oppPenaltyARect().contains(wm->getBall().pos) && wm->ourRobot(id).pos.dist(wm->getBall().pos) < 10) {

		spin(id, Field::oppGoal(), 50);

	}
}
