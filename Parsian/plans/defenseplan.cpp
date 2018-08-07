#include "stdafx.h"
#include "../soccer.h"

void Soccer::Defense(int id[], int size) {
	
	const rcsc::Vector2D& bp = wm->getBall().pos + wm->getBall().vel*0.2;
	const double def_w = -Field::width / 2 + Field::penaltyBwidth;
	switch (size)
	{
	case 1:
		gotoPoint(id[0], rcsc::Vector2D(def_w, bp.y), rcsc::Vector2D(0, 1000));
		break;
	case 2:
		gotoPoint(id[0], rcsc::Vector2D(def_w, bp.y+10), rcsc::Vector2D(0, 1000));
		gotoPoint(id[1], rcsc::Vector2D(def_w, bp.y-10), rcsc::Vector2D(0, 1000));
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