#pragma once

#include <stdio.h>
#include <stdlib.h> 
#include <thread>
#include <iostream>
#include <fstream>
#include "base.h"
#include "worldmodel.h"

class Soccer
{
public:
	Soccer();
	~Soccer();

	void init(const char* _teamName);
	void updateWM(const CWorldModel& _wm);
	void updateGS(const PlayMode& _gs);
	void setFormerRobots(Robot* robots);
	void setLaterRobots(Robot* robots);
private:
	const char* teamName;
	CWorldModel wm;
	std::thread* m_handle;
	std::ofstream* logs;

};

