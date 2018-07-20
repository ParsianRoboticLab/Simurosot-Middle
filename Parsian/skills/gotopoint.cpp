#include "stdafx.h"
#include "../soccer.h"
#include "../util/bangbang.h"
#include "../util/pid.h"

void Soccer::gotoPoint(Robot* robot, int id, const rcsc::Vector2D&  targetPos, const rcsc::Vector2D& targetVel, double pidDist1, double pidDist2) {
    double pidV = posPID[id].run(wm->ourRobot(id).pos.dist(targetPos));
    double pidW = angPID[id].run(wm->ourRobot(id).th - targetVel.th().radian());

    double bbV;
    bangBangSpeed(wm->ourRobot(id).pos, wm->ourRobot(id).vel, targetPos, targetVel, bbV);
    
    double V, W;
    if (wm->ourRobot(id).pos.dist(targetPos) < pidDist1) {
        double t = (wm->ourRobot(id).pos.dist(targetPos) - pidDist2) / pidDist1;
        t = std::fmax(t, 0);
        V = (t * bbV) + (1 - t) * pidV;
    }
    

}