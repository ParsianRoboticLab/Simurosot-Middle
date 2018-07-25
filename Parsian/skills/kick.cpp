#include "stdafx.h"
#include "../soccer.h"
#include "../util/bangbang.h"
#include "../util/pid.h"

void Soccer::kick(int id, const rcsc::Vector2D&  targetPos) {

	rcsc::Vector2D ballPos{ wm->getBall().pos + wm->getBall().vel*(5. / 5.) };
	rcsc::Vector2D robotPos{ wm->ourRobot(id).pos + wm->ourRobot(id).vel*(5. / 5.) };
	rcsc::Vector2D norm{ ballPos - targetPos };
	norm = norm.normalize();
	rcsc::Vector2D prependicular{ norm.rotatedVector(90) };
	rcsc::Vector2D behindPos{ ballPos + norm * 20 };
	rcsc::Vector2D avoidPos{ ballPos + prependicular * 10 };

	if (wm->ourRobot(id).pos.dist(behindPos) > 25)
		gotoPoint(id, behindPos, targetPos);
	else
		gotoPoint(id, ballPos, targetPos);
}
