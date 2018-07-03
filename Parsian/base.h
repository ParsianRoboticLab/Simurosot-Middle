#define YELLOW

const long ROBOT_COUNT = 5;
const double PI = 3.1415926535;

typedef struct
{
	double x, y, z;
} Vector3D;


typedef struct
{
	long left, right, top, bottom;
} Bounds;


typedef struct
{
	Vector3D pos;
	double rotation;
	double velocityLeft, velocityRight;
} Robot;


typedef struct
{
	Vector3D pos;
	double rotation;
} OpponentRobot;


typedef struct
{
	Vector3D pos;
} Ball;


typedef struct
{
	Robot home[ROBOT_COUNT];
	OpponentRobot opponent[ROBOT_COUNT];
	Ball currentBall, lastBall, predictedBall;
	Bounds fieldBounds, goalBounds;
	long gameState;
	long whosBall;
	void *userData;
} Environment;

enum PlayMode {
	PM_PlayOn = 0,           //  
	PM_FreeBall_LeftTop,     //   1
	PM_FreeBall_LeftBot,     //   2
	PM_FreeBall_RightTop,    //   3
	PM_FreeBall_RightBot,    //   4
	PM_PlaceKick_Yellow,     //   5
	PM_PlaceKick_Blue,       //   6
	PM_PenaltyKick_Yellow,   //   7
	PM_PenaltyKick_Blue,     //   8
	PM_FreeKick_Yellow,      //   9
	PM_FreeKick_Blue,        //   10
	PM_GoalKick_Yellow,      //   11
	PM_GoalKick_Blue         //   12
};