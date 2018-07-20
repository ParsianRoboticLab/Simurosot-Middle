#include "stdafx.h"
#include "../soccer.h"

std::ifstream ifile;
PID p;
void Soccer::playon() {

	if (env->currentBall.pos.x > 10) ballInOurSide = false;
	else if (env->currentBall.pos.x < 10) ballInOurSide = true;

	setRobotVel(1, 1, 0);
//	Goalie(env);
	Position(&robots[2], 0, 0);
	//Position(&robots[1], -50, -50);
	Position(&robots[3], -50, -50);
	Position(&robots[4], -50, -50);

}