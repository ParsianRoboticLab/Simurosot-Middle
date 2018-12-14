#ifndef _KNOWLEDGE_HEADER
#define _KNOWLEDGE_HEADER

#include "base.h"
#include "geom.h"
#include "worldmodel.h"
#include "field.h"
#include "util\pid.h"


double ballPossession(const CWorldModel* _wm); // 0 means fully for them and 1 means fully for us
void getRobotWheel(double w, double vel_tan, double& right_wheel, double& left_wheel);
void getRobotWheelPID(const CRobot& r, double w, double vel_tan, double& right_wheel, double& left_wheel);

//// HELPER DEMO
void PredictBall(Environment *pEnv);
void Goalie1(Robot *robot, Environment *pEnv);
void NearBound2(Robot *robot, double vl, double vr, Environment *pEnv);
void Attack2(Robot *robot, Environment *pEnv);
void Defend(Robot *robot, Environment *pEnv, double low, double high);
void MoonAttack(Robot *robot, Environment *pEnv);
void MoonFollowOpponent(Robot *robot, OpponentRobot *opponent);
void Velocity(Robot *robot, double vl, double vr);
void Angle(Robot *robot, double desired_angle);
void Position(Robot *robot, double x, double y);
void Position(Environment * pEnv, int id, double x, double y);
void Goalie(Environment* pEnv);
void LeftWing(Environment* pEnv, int id);
void RightWing(Environment* pEnv, int id);
void CenterDefender(Environment* pEnv, int id);
void CenterAttacker(Environment* pEnv, int id);



#endif _KNOWLEDGE_HEADER