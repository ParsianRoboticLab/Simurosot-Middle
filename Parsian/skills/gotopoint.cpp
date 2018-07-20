#include "stdafx.h"
#include "../soccer.h"
#include "../util/bangbang.h"
#include "../util/pid.h"

void gotoPoint(Robot* robot, int id, const rcsc::Vector2D&  targetPos, const rcsc::Vector2D& targetVel, double pidDist1, double pidDist2) {
    double pidV = pidPos[id].run(wm.our[id].pos.dist(targetPos));
    double pidW = pidAng[id].run(wm.our[id].dir.th().radian() - targetVel.th().radian());

    double bbV;
    bangBangSpeed(wm.our[i].pos, wm.our[id].vel, targetPos, targetVel, bbV);
    
    double V, W;
    if (wm.our[i].dist(targetPos) < pidDist1) {
        double t = (wm.our[i].dist(targetPos) - pidDist2) / pidDist1;
        t = max(t, 0);
        V = (t * bbV) + (1 - t) * pidV;
    }
    

}