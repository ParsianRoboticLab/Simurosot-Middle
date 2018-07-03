// parsian.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "parsian.h"

Soccer soccer;
#ifdef YELLOW
// Set the team name for yellow side.
PARSIAN_API void SetYellowTeamName(char* teamName) {
	// MUST change the name into your own team name!
	strcpy(teamName, "Parsian");
	soccer.init(teamName, true);
}
#else
// Set the team name for blue side.
PARSIAN_API void SetBlueTeamName(char* teamName) {
	// MUST change the name into your own team name!
	strcpy(teamName, "Parsian");
	soccer.init(teamName, false);
}
#endif

// Set the positions and rotations of your team when your team place robots first.
// [IN] gameState : the state of game
// [OUT] robots : robots data for placing,including position and rotation
PARSIAN_API void SetFormerRobots(PlayMode gameState, Robot robots[]) {
	soccer.updateGS(gameState);
	soccer.setFormerRobots(robots);
	
}

// Set the positions and rotations of your team when your team place robots last.
// [IN] gameState : the state of game
// [IN] formerRobots : the data of first placing team
// [IN] ball : the position of the ball
// [OUT] laterRobots : robots data for placing,including position and rotation
PARSIAN_API void SetLaterRobots(PlayMode gameState, Robot formerRobots[],
	Vector3D ball, Robot laterRobots[]) {
	soccer.updateGS(gameState);
	soccer.setLaterRobots(laterRobots, formerRobots, ball);
}


// Set the position of the ball when your team get the Goal Kick.
// [IN] gameState : the state of game
// [IN] pBall : the position of the ball
PARSIAN_API void SetBall(PlayMode gameState, Vector3D * pBall) {
	soccer.updateGS(gameState);
	soccer.setBall(pBall);
}

// Strategy for your team using centimeter unit, cartesian coordinate system.
// The origin is at the left bottom of the field.
PARSIAN_API void RunStrategy(Environment *pEnv) {
	soccer.updateGS(PM_PlayOn);
	soccer.updateWM(pEnv);
	soccer.run();
}