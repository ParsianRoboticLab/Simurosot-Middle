#include "stdafx.h"
#include "../soccer.h"

void Soccer::Pos(int id[], int size) {
	
	const rcsc::Vector2D& ballPos = wm->getBall().pos + wm->getBall().vel*0.2;
	
	switch (size)
	{
	case 1:
	{
		double dist0{ wm->getBall().pos.dist(wm->ourRobot(id[0]).pos) };
		if (dist0 < 40)
			spin(id[0], Field::oppGoal(), 30);
		if (ballPos.y < -Field::height / 4)
			gotoPoint(id[0], rcsc::Vector2D(ballPos.x, 0), rcsc::Vector2D(1000, 0));
		else if (ballPos.y > Field::height / 4)
			gotoPoint(id[0], rcsc::Vector2D(ballPos.x, 0), rcsc::Vector2D(1000, 0));
		else
			if (wm->ourRobot(id[0]).pos.y > 0)
				gotoPoint(id[0], rcsc::Vector2D(ballPos.x, 60), rcsc::Vector2D(1000, 0));
			else
				gotoPoint(id[0], rcsc::Vector2D(ballPos.x, -60), rcsc::Vector2D(1000, 0));

		break;
	}
	case 2:
	{
		double dist0{ wm->getBall().pos.dist(wm->ourRobot(id[0]).pos) };
		double dist1{ wm->getBall().pos.dist(wm->ourRobot(id[1]).pos) };
		if (dist1 < 40)
			spin(id[1], Field::oppGoal(), 30);
		if (dist0 < 40)
			spin(id[0], Field::oppGoal(), 30);
		if (ballPos.y < -Field::height / 4) {
			gotoPoint(id[0], rcsc::Vector2D(ballPos.x, Field::penaltyBheight / 2), rcsc::Vector2D(1000, 0));
			gotoPoint(id[1], rcsc::Vector2D(80, 0), rcsc::Vector2D(1000, 0));
		}
		else if (ballPos.y > Field::height / 4) {
			gotoPoint(id[0], rcsc::Vector2D(ballPos.x, -Field::penaltyBheight / 2), rcsc::Vector2D(1000, 0));
			gotoPoint(id[1], rcsc::Vector2D(80, 0), rcsc::Vector2D(1000, 0));
		}
		else {
			// matching
			int lower = -1, upper = -1;
			if (wm->ourRobot(id[0]).pos.y > 0) {
				upper = id[0];
				lower = id[1];
			}
			else {
				upper = id[1];
				lower = id[0];
			}
			gotoPoint(upper, rcsc::Vector2D(ballPos.x, Field::penaltyBheight / 2), rcsc::Vector2D(1000, 0));
			gotoPoint(lower, rcsc::Vector2D(ballPos.x, -Field::penaltyBheight / 2), rcsc::Vector2D(1000, 0));
		}
		break;
	}
	default:
		break;
	}
}