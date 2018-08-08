#include "stdafx.h"
#include "../soccer.h"

void Soccer::Defense(int id[], int size) {
	
	const rcsc::Vector2D& bp = wm->getBall().pos - wm->getBall().vel*0.5;
	const double def_w = -Field::width / 2 + Field::penaltyAwidth + 5;
	double y = bp.y;
	switch (size)
	{
	case 1:
		if (y < -Field::penaltyAheight + 5) y = -Field::penaltyAheight / 2 + 2;
		if (y > Field::penaltyAheight / 2 - 5) y = Field::penaltyAheight / 2 - 2;

		if (wm->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 10)
			gotoPoint(id[0], rcsc::Vector2D(def_w, y), rcsc::Vector2D(0, 1000));
		else {
			if (wm->getBall().pos.y > 0) {
				gotoPoint(id[0], rcsc::Vector2D(bp.x - 10, Field::penaltyAheight/2 + 15), rcsc::Vector2D(1000, 0));
			}
			else {
				gotoPoint(id[0], rcsc::Vector2D(bp.x - 10, -Field::penaltyAheight/2 - 15), rcsc::Vector2D(1000, 0));
			}
		}

		if (wm->getBall().pos.dist(wm->ourRobot(id[0]).pos) < 8.5) {
			LOG("SPIN GOALIE");
			if (wm->getBall().pos.y > 0) setRobotVel(id[0], 0, 30);
			else setRobotVel(id[0], 0, -30);
		}

		break;
	case 2:
		if (y < -Field::penaltyAheight + 5) y = -Field::penaltyAheight / 2 + 2;
		if (y > Field::penaltyAheight / 2 - 5) y = Field::penaltyAheight / 2 - 2;

		if (wm->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 50)
			gotoPoint(id[0], rcsc::Vector2D(def_w, y + 5), rcsc::Vector2D(0, 1000));
		else {
			if (wm->getBall().pos.y > 0) {
				gotoPoint(id[0], rcsc::Vector2D(bp.x - 10, Field::penaltyAheight / 2 + 15), rcsc::Vector2D(1000, 0));
			}
			else {
				gotoPoint(id[0], rcsc::Vector2D(def_w, y), rcsc::Vector2D(0, 1000));
			}
		}
		if (wm->getBall().pos.dist(wm->ourRobot(id[0]).pos) < 8.5 && wm->getBall().pos.x > -Field::width/2 + Field::penaltyAwidth + 5) {
			LOG("SPIN GOALIE");
			if (wm->getBall().pos.y > 0) setRobotVel(id[0], 0, 30);
			else setRobotVel(id[0], 0, -30);
		}

		if (wm->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 50)
			gotoPoint(id[1], rcsc::Vector2D(def_w, y - 5), rcsc::Vector2D(0, 1000));
		else {
			if (wm->getBall().pos.y > 0) {
				gotoPoint(id[1], rcsc::Vector2D(def_w, y), rcsc::Vector2D(0, 1000));
			}
			else {
				gotoPoint(id[1], rcsc::Vector2D(bp.x - 10, -Field::penaltyAheight / 2 - 15), rcsc::Vector2D(1000, 0));
			}
		}

		if (wm->getBall().pos.dist(wm->ourRobot(id[0]).pos) < 8.5 && wm->getBall().pos.x > -Field::width / 2 + Field::penaltyAwidth + 5) {
			LOG("SPIN GOALIE");
			if (wm->getBall().pos.y > 0) setRobotVel(id[0], 0, 30);
			else setRobotVel(id[0], 0, -30);
		}
		break;
	case 3:
		if (bp.x < def_w + 20) {
			gotoPoint(id[0], rcsc::Vector2D(bp.x, -Field::penaltyBheight/2), rcsc::Vector2D(1000, 0)); //Left
			gotoPoint(id[1], rcsc::Vector2D(def_w, bp.y), rcsc::Vector2D(0, 1000)); // Center
			gotoPoint(id[2], rcsc::Vector2D(bp.x, Field::penaltyBheight/2), rcsc::Vector2D(1000, 0)); // Right

		}
		else {
			gotoPoint(id[0], rcsc::Vector2D(def_w, bp.y - 20), rcsc::Vector2D(0, 1000));
			gotoPoint(id[1], rcsc::Vector2D(def_w, bp.y), rcsc::Vector2D(0, 1000));
			gotoPoint(id[2], rcsc::Vector2D(def_w, bp.y + 20), rcsc::Vector2D(0, 1000));

		}
		
		break;
	default:
		break;
	}
}