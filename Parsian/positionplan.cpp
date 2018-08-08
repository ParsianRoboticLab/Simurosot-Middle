#include "stdafx.h"
#include "../soccer.h"

void Soccer::Pos(int id[], int size) {
	
	const rcsc::Vector2D& bp = wm->getBall().pos + wm->getBall().vel*0.2;
	
	switch (size)
	{
	case 1:
		if (bp.y < -Field::height / 4)
			gotoPoint(id[0], rcsc::Vector2D(bp.x, 0), rcsc::Vector2D(1000, 0));
		else if (bp.y > Field::height / 4) 
			gotoPoint(id[0], rcsc::Vector2D(bp.x, 0), rcsc::Vector2D(1000, 0));
		else 
			if (wm->ourRobot(id[0]).pos.y > 0)
				gotoPoint(id[0], rcsc::Vector2D(bp.x, 60), rcsc::Vector2D(1000, 0));
			else
				gotoPoint(id[0], rcsc::Vector2D(bp.x, -60), rcsc::Vector2D(1000, 0));

		break;
	case 2:
		if (bp.y < -Field::height / 4) {
			gotoPoint(id[0], rcsc::Vector2D(bp.x, Field::penaltyBheight/2), rcsc::Vector2D(1000, 0));
			gotoPoint(id[1], rcsc::Vector2D(60, 0), rcsc::Vector2D(1000, 0));
		}
		else if (bp.y > Field::height / 4) {
			gotoPoint(id[0], rcsc::Vector2D(bp.x, -Field::penaltyBheight/2), rcsc::Vector2D(1000, 0));
			gotoPoint(id[1], rcsc::Vector2D(60, 0), rcsc::Vector2D(1000, 0));
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
			gotoPoint(upper, rcsc::Vector2D(bp.x, Field::penaltyBheight / 2), rcsc::Vector2D(1000, 0));
			gotoPoint(lower, rcsc::Vector2D(bp.x, -Field::penaltyBheight / 2), rcsc::Vector2D(1000, 0));
		}
		break;
	default:
		break;
	}
}