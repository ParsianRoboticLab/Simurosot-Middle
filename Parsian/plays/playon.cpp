#include "stdafx.h"
#include "../soccer.h"

std::ifstream ifile;
PID p;
void Soccer::playon() {

	if (env->currentBall.pos.x > 10) ballInOurSide = false;
	else if (env->currentBall.pos.x < 10) ballInOurSide = true;

	Goalie(0);

	int playmake = -1;
	double pm_cost = 1000000000.0;
	for (int i = 1; i < 5; i++) {
		double t_cost = wm->ourRobot(i).pos.dist(wm->getBall().pos + wm->getBall().vel + rcsc::Vector2D(-20,0));
		if (t_cost < pm_cost) {
			pm_cost = t_cost;
			playmake = i;
		}
	}

	int defenseNum = -1;
	if (wm->getBall().pos.x < -30) defenseNum = 3;
	else if (wm->getBall().pos.x > 30) defenseNum = 1;
	else defenseNum = 2;

	int defense[3] = { -1, -1, -1 };
	
	for (int d = 0; d < defenseNum; d++) {
		int bestID = -1;
		int best = 100000000;
		for (int i = 1; i < 5; i++) {
			if (i == playmake) continue;
			bool same = false;
			for (int j = 0; j < 3; j++) if (defense[j] == i) same = true;
			if (same) continue;

			double t = wm->ourRobot(i).pos.dist(Field::ourGoal());
			if (t < best) {
				best = t;
				bestID = i;
			}
		}
		defense[d] = bestID;
	}
	LOG("DEF:  " << defense[0] << defense[1] << defense[2]);
	LOG("PM:   " << playmake);
	
	Defense(defense, defenseNum);
	//gotoPoint(0, rcsc::Vector2D(-Field::width/2, wm->getBall().pos.y), rcsc::Vector2D(0, 1000));
	//gotoPoint(2, rcsc::Vector2D(0, 0), Field::oppGoal());
	kick(playmake, Field::oppGoal());
	//gotoPoint(3, rcsc::Vector2D(-Field::width / 2 + Field::penaltyBheight, wm->getBall().pos.y + 10), rcsc::Vector2D(0, 1000));
	//gotoPoint(4, rcsc::Vector2D(-Field::width / 2 + Field::penaltyBheight, wm->getBall().pos.y - 10), rcsc::Vector2D(0, 1000));

	//setRobotVel(1, 1, 0);
//	Goalie(env);
	//Position(&robots[2], 0, 0);
	//Position(&robots[1], -50, -50);
	//Position(&robots[3], -50, -50);
	//Position(&robots[4], -50, -50);

}