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

enum class GameState {
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
	Blue   = 1
}

class CWorldModel {
public:
	CWorldModel();
	~CWorldModel();
    GameState gs; // Game State
    TColor teamColor;
	const CMovingObject& ball() { return ball; }
	const Robot& our(const unsigned int & _id) { return our[_id]; }
	const Robot& opp(const unsigned int & _id) { return opp[_id]; }
	const Robot* ourRobots() { return our; } 
	const Robot* oppRobots() { return opp; }
	void increaseLoop() { loop++; }
	unsigned long long getLoop() { return loop; }
	void update(const Environment* _env);

private:
    CMovingObject ball;
    CRobot our[ROBOT_COUNT];
    CRobot opp[ROBOT_COUNT];
    unsigned long long loop;

	/// Tracker and Filters
	
};
#endif // _WORLD_MODEL_HEADER_