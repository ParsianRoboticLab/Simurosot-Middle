#pragma once

#ifdef PARSIAN_EXPORTS
#define PARSIAN_API __declspec(dllexport)
#else
#define PARSIAN_API __declspec(dllimport)
#endif

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <thread>

#include "proto/messages_parsian_simurosot_data_wrapper.pb.h"
#include "soccer.h"
#include "base.h"
extern "C" { 
#include "net/src/msock.h" 
}

#include <windows.h>


// #############################################################################################
PARSIAN_API void SetFormerRobots(PlayMode gameState, Robot robots[]);
PARSIAN_API void SetLaterRobots(PlayMode gameState, Robot formerRobots[], Vector3D ball, Robot laterRobots[]);
PARSIAN_API void SetBall(PlayMode gameState, Vector3D * pBall);
PARSIAN_API void RunStrategy(Environment *pEnv);
PARSIAN_API void SetYellowTeamName(char* teamName);

// #############################################################################################
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


// #############################################################################################