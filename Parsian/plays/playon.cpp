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
	Position(&robots[2], 70, 20);
	Position(&robots[1], -50, -50);
	Position(&robots[3], -50, -50);
	Position(&robots[4], -50, -50);

}