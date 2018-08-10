#include "stdafx.h"
#include "../soccer.h"

std::ifstream ifile;
PID p;
void Soccer::playon() {
	Goalie(0);
	int playmake = -1;
	double pm_cost = 1000000000.0;
	for (int i = 1; i < 5; i++) {
		double t_cost = wm->ourRobot(i).pos.dist(wm->getBall().pos + wm->getBall().vel + rcsc::Vector2D(-20, 0));
		if (i == last_pm) t_cost -= 10;
		if (wm->ourRobot(i).pos.x > wm->getBall().pos.x + 10) t_cost += 10000;
		if (t_cost < pm_cost) {
			pm_cost = t_cost;
			playmake = i;
		}
	}
	last_pm = playmake;

	PlayMake(playmake);
	
	int defenseNum = -1;
	if (wm->getBall().pos.x < -30) defenseNum = 3;
	else if (wm->getBall().pos.x > 30) defenseNum = 1;
	else defenseNum = 2;
	defenseNum = 1;
	int defense[3] = { -1, -1, -1 };
	rcsc::Vector2D poses[3] = { Field::ourGoal(), Field::ourGoalB(), Field::ourGoalT() };
	for (int d = 0; d < defenseNum; d++) {
		int bestID = -1;
		int best = 100000000;
		for (int i = 1; i < 5; i++) {
			if (i == playmake) continue;
			bool same = false;
			for (int j = 0; j < 3; j++) if (defense[j] == i) same = true;
			if (same) continue;
			
			double t = wm->ourRobot(i).pos.dist(poses[d]);
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
	int other[2] = { -1, -1 };
	for (int o = 0; o < 2; o++) {
		for (int i = 1; i < 5; i++) {
			if (i == playmake) continue;
			bool same = false;
			for (int j = 0; j < 3; j++) if (defense[j] == i) same = true;
			for (int j = 0; j < 2; j++) if (other[j] == i) same = true;
			if (same) continue;
			other[o] = i;
		}
	}
	Pos(other, 3 - defenseNum);
	LOG("DEF:  " << defense[0] << defense[1] << defense[2]);
	LOG("PM:   " << playmake);
	LOG("POS:  " << other[0] << other[1]);

	//kick(playmake, Field::oppGoal());
	
}