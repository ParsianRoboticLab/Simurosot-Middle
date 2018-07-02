#ifndef _WORLD_MODEL_HEADER_
#define _WORLD_MODEL_HEADER_

#include "geom.h"
#include "base.h"

using namespace rcsc;

struct CMovingObject {
    Vector2D pos, vel, acc;
};

struct CRobot : public CMovingObject {
    unsigned int id;
    double w, th;
};

class CWorldModel {
public:
    GameState gs; // Game State
    TColor teamColor;

private:
    CMovingObject ball;
    CRobot our[ROBOT_COUNT];
    CRobot opp[ROBOT_COUNT];
    unsigned long long loop;
};

#endif // _WORLD_MODEL_HEADER_