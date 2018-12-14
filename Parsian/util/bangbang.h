#ifndef _BANGBANG_HEADER_
#define _BANGBANG_HEADER_ 

#include "../geom.h"
#include "../base.h"
#include <cmath>


enum class BBState : int {
    BBAcc = 0,
    BBDec = 1
};


BBState decidePlan(const rcsc::Vector2D& pos1, const rcsc::Vector2D& pos2, const rcsc::Vector2D& vel2);

void bangBangSpeed(rcsc::Vector2D pos1, rcsc::Vector2D vel1, rcsc::Vector2D pos2, rcsc::Vector2D vel2, double & _Vx);

#endif // _BANGBANG_HEADER_