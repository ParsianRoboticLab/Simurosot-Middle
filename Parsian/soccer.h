#pragma once

#include <stdio.h>
#include <stdlib.h> 
#include <thread>
#include <iostream>
#include <fstream>
#include "base.h"
#include "proto/messages_parsian_simurosot_worldmodel.pb.h"

class Soccer
{
public:
	Soccer();
	~Soccer();

	void init(const char* _teamName);
	void updateWM(const WorldModel& _wm);
	void updateGS(const PlayMode& _gs);
	void setFormerRobots();
	void update(const )
	void getRobots(Robot* _robots);
private:
	const char* teamName;
	WorldModel wm;
	std::thread* m_handle;
	std::ofstream* logs;

};

