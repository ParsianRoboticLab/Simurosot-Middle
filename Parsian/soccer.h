#pragma once

#include <stdio.h>
#include <stdlib.h> 
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>
#include "base.h"
#include "worldmodel.h"
#include "knowledge.h"

class Soccer
{
public:
	Soccer();
	~Soccer();

	void init(const char* _teamName, bool isYellow);
	void updateWM(Environment* _env);
	void updateGS(const PlayMode& pm);
	void setFormerRobots(Robot* robots);
	void setLaterRobots(Robot* robots, const Robot* oppRobots, const Vector3D& _ball);
	void setBall(Vector3D* ball);
	void run(Robot* _robots);
private:
	const char* teamName;
	CWorldModel* wm;
	Environment* env;
	Robot* robots;
	// Threads!
	std::thread* t_network; // For Read From Network
	//static void f_network(const CWorldModel* wm, const Environment* env);
	
	// LOGS
	std::ofstream* log_env;
	std::ofstream* log_cmd;
	std::ofstream* log_wm;
	std::ofstream* log;

	// PLAYS
	void playon();
	void freeballLT();
	void freeballLB();
	void freeballRT();
	void freeballRB();
	void ourKO();
	void oppKO();
	void ourGK();
	void oppGK();
	void ourFK();
	void oppFK();
	void ourPK();
	void oppPK();


	//// PlayOn
	bool ballInOurSide;

};

