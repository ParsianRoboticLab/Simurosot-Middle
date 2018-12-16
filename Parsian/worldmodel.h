#ifndef _WORLD_MODEL_HEADER_
#define _WORLD_MODEL_HEADER_

#include "geom.h"
#include "base.h"
#include "field.h"

struct CMovingObject {
    rcsc::Vector2D pos, vel, acc;
};

struct CRobot : public CMovingObject {
    unsigned int id;
    double w, th;
};

enum class GameMode {
	PlayOn            = 0,
	FreeBall_LeftTop  = 1,
	FreeBall_LeftBot  = 2,
	FreeBall_RightTop = 3,
	FreeBall_RightBot = 4,
	OurKickOff        = 5,
	OppKickOff        = 6,
	OurPenaltyKick    = 7,
	OppPenaltyKick    = 8,
	OurFreeKick       = 9,
	OppFreeKick       = 10,
	OurGoalKick       = 11,
	OppGoalKick       = 12
};

enum class TColor {
	Yellow = 0,
	Blue = 1
};

class CWorldModel {
public:
	CWorldModel();
	~CWorldModel();
    GameMode gs; // Game State
    TColor teamColor;
	const CMovingObject& getBall() const { return ball; }
	const CRobot& ourRobot(const unsigned int & _id) const { return our[_id]; }
	const CRobot& oppRobot(const unsigned int & _id) const { return opp[_id]; }
	const CRobot* ourRobots() const { return our; } 
	const CRobot* oppRobots() const { return opp; }
	void increaseLoop() { loop++; }
	unsigned long long getLoop() const { return loop; }
	void update(const Environment* _env);

private:
    CMovingObject ball, lastBall;
    CRobot our[ROBOT_COUNT];
    CRobot opp[ROBOT_COUNT];
	CRobot lastOur[ROBOT_COUNT];
	CRobot lastOpp[ROBOT_COUNT];
    unsigned long long loop;	
};
#endif // _WORLD_MODEL_HEADER_