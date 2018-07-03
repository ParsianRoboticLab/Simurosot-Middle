#include "stdafx.h"
#include "../soccer.h"

void Soccer::playon() {

	if (env->currentBall.pos.x > 10) ballInOurSide = false;
	else if (env->currentBall.pos.x < 10) ballInOurSide = true;

	Goalie(env);

	if (ballInOurSide) {
		// Defense(3)
	}
	else {

	}
	Position(&robots[1], 0, 0);
	Position(&robots[2], 10, 10);
	Position(&robots[3], 20, 20);
	Position(&robots[4], 30, 30);

}