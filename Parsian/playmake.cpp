#include "stdafx.h"
#include "../soccer.h"


void Soccer::PlayMake(int id) {
	double margin{10};
	/*if (wm->ourRobot(id).vel.length() > 2)
		margin = 17;*/
	if (rcsc::Rect2D{ Field::width / 2 - Field::penaltyBwidth - margin, -Field::penaltyBheight / 2 - margin, Field::penaltyBwidth, Field::penaltyBheight + margin }.contains(wm->getBall().pos)) {
		spin(id, Field::oppGoal(), 40);
	}
	else if (Field::ourPenaltyBRect().contains(wm->getBall().pos)) {
		gotoPoint(id, rcsc::Vector2D(0, 0), rcsc::Vector2D(0, 1000));
	}
	else  {
		kick(id, Field::oppGoal());
	}
}