#include "stdafx.h"
#include "../soccer/soccer.h"

void Soccer::PlayMake(int id) {
	double margin{20};
	if (rcsc::Rect2D{ Field::width / 2 - Field::penaltyAwidth - margin, -Field::penaltyAheight / 2 - margin, Field::penaltyAwidth, Field::penaltyAheight + margin }.contains(wm->getBall().pos)
		&& wm->ourRobot(id).pos.dist(wm->getBall().pos) < 9) {
		spin(id, Field::oppGoal(), 40);
	}
	else if (Field::ourPenaltyBRect().contains(wm->getBall().pos)) {
		gotoPoint(id, rcsc::Vector2D(0, 0), rcsc::Vector2D(0, 1000));
	}
	else  {
		kick(id, Field::oppGoal() + rcsc::Vector2D(15, 0));
	}
}