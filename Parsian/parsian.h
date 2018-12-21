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
#include "soccer/soccer.h"
#include "util/base.h"

#include <windows.h>


// #############################################################################################
PARSIAN_API void SetFormerRobots(PlayMode gameState, Robot robots[]);
PARSIAN_API void SetLaterRobots(PlayMode gameState, Robot formerRobots[], Vector3D ball, Robot laterRobots[]);
PARSIAN_API void SetBall(PlayMode gameState, Vector3D * pBall);
PARSIAN_API void RunStrategy(Environment *pEnv);
#ifdef YELLOW
PARSIAN_API void SetYellowTeamName(char* teamName);
#else
PARSIAN_API void SetBlueTeamName(char* teamName);
#endif
