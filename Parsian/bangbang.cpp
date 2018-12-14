#include "stdafx.h"
#include "util\bangbang.h"

BBState decidePlan(const rcsc::Vector2D& pos1, const rcsc::Vector2D& pos2, const rcsc::Vector2D& vel2) {
	double decDistance;
	double lvel2 = vel2.length();
	decDistance = (lvel2 * lvel2 - vel_max * vel_max) / (-2 * std::fabs(dec_max));
	if ((decDistance > 0) && (pos1.dist(pos2) < decDistance)) return BBState::BBDec;
	else return BBState::BBAcc;
}

void bangBangSpeed(rcsc::Vector2D pos1, rcsc::Vector2D vel1, rcsc::Vector2D pos2, rcsc::Vector2D vel2, double & _Vx) {

	//////////////////////// dec calculations
	double moreDec = 0.7;
	double decOffset = 0.6;
	double vDes = 0;
	switch (decidePlan(pos1, pos2, vel2)) {
	case BBState::BBAcc:
		vDes = vel_max;
		break;
	case BBState::BBDec:
		double lvel2 = vel2.length();
		vDes = std::sqrt(lvel2 *  lvel2 + 2 * dec_max * pos1.dist(pos2)*moreDec) - decOffset;
		break;
	}
	// trajectoryPlanner(vel1);
	_Vx = vDes;
}