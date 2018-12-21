#ifndef _KNOWLEDGE_HEADER
#define _KNOWLEDGE_HEADER

#include "base.h"
#include "../geom/geom.h"
#include "worldmodel.h"
#include "field.h"
#include "pid.h"


double ballPossession(const CWorldModel* _wm); // 0 means fully for them and 1 means fully for us
void getRobotWheel(double w, double vel_tan, double& right_wheel, double& left_wheel);
void getRobotWheelPID(const CRobot& r, double w, double vel_tan, double& right_wheel, double& left_wheel);

#endif _KNOWLEDGE_HEADER