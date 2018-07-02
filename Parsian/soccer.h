#pragma once

#include <stdio.h>
#include <stdlib.h> 
#include <windows.h>
#include <thread>
#include <iostream>
#include <fstream>

#include "proto/messages_parsian_simurosot_worldmodel.pb.h"

struct wm {

};

class Soccer
{
public:
	Soccer();
	~Soccer();

	void init(std::thread* handle, std::ofstream* _logs);
	void updateWM(const WorldModel& _wm);
private:
	WorldModel wm;
	std::thread* m_handle;
	std::ofstream* logs;

};

