#include "../geom.h"
#include "../base.h"
#include <cmath>

using namespace rcsc;

enum BBState {
    BBAcc = 0,
    BBDec = 1
};


BBState decidePlan(const Vector2D& pos1, const Vector2D& pos2, const Vector2D& vel2) {
    double decDistance;
    double lvel2 = vel2.length();
    decDistance = (lvel2 * lvel2 - vel_max * vel_max) / (-2 * std::fabs(dec_max)) ;
    if((decDistance > 0) && (pos1.dist(pos2) < decDistance) ) return BBDec;
    else return BBAcc;
}

void bangBangSpeed(Vector2D pos1, Vector2D vel1, Vector2D pos2, Vector2D vel2, double & _Vx) {

    //////////////////////// dec calculations
    double moreDec = 0.7;
    double decOffset = 0.6;
    double vDes = 0;
    switch(decidePlan(pos1, pos2, vel2)) {
    case BBAcc:
        vDes = vel_max;
        break;
    case BBDec:
        double lvel2 = vel2.length();
        vDes = std::sqrt( lvel2 *  lvel2 + 2 * dec_max * pos1.dist(pos2)*moreDec)- decOffset ;
        break;
    }
    // trajectoryPlanner(vel1);
    _Vx =  vDes;
}
