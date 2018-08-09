#include "stdafx.h"
#include "../soccer.h"


void Soccer::PlayMake(int id) {
	if (!Field::ourPenaltyBRect().contains(wm->getBall().pos)) {
		kick(id, Field::oppGoal());
	}
	else {
		gotoPoint(id, rcsc::Vector2D(0, 0), rcsc::Vector2D(0, 1000));
	}
}