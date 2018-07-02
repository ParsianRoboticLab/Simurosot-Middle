#include "stdafx.h"
#include "soccer.h"


Soccer::Soccer() {
	m_handle = NULL;
	
}


Soccer::~Soccer() {
	m_handle->join();
	delete m_handle;
	*logs << "\n THE END. \n";
	logs->close();
}

void Soccer::init(const char* _teamName) : teamName(_teamName){

}

void Soccer::updateWM(const WorldModel & _wm) {
	wm = _wm;
}

void Soccer::setFormerRobots() {
	// This is just for a demo. You may set your own data.
	switch (gameState) {
	case 1:
		robots[0].pos.x = 5;
		robots[0].pos.y = 100;
		robots[0].rotation = 90;
		robots[1].pos.x = 25;
		robots[1].pos.y = 150;
		robots[1].rotation = 0;
		robots[2].pos.x = 22;
		robots[2].pos.y = 80;
		robots[2].rotation = 0;
		robots[3].pos.x = 60;
		robots[3].pos.y = 80;
		robots[3].rotation = 0;
		robots[4].pos.x = 80;
		robots[4].pos.y = 50;
		robots[4].rotation = 0;
		break;
	case 2:
		robots[0].pos.x = 5;
		robots[0].pos.y = 80;
		robots[0].rotation = 90;
		robots[1].pos.x = 25;
		robots[1].pos.y = 30;
		robots[1].rotation = 0;
		robots[2].pos.x = 22;
		robots[2].pos.y = 100;
		robots[2].rotation = 0;
		robots[3].pos.x = 60;
		robots[3].pos.y = 100;
		robots[3].rotation = 0;
		robots[4].pos.x = 80;
		robots[4].pos.y = 130;
		robots[4].rotation = 0;
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		robots[0].pos.x = 5;
		robots[0].pos.y = 90;
		robots[0].rotation = 90;
		robots[1].pos.x = 40;
		robots[1].pos.y = 90;
		robots[1].rotation = 0;
		robots[2].pos.x = 100;
		robots[2].pos.y = 100;
		robots[2].rotation = 0;
		robots[3].pos.x = 95;
		robots[3].pos.y = 80;
		robots[3].rotation = 0;
		robots[4].pos.x = 125;
		robots[4].pos.y = 90;
		robots[4].rotation = 0;
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		robots[0].pos.x = 5;
		robots[0].pos.y = 90;
		robots[0].rotation = 90;
		robots[1].pos.x = 130;
		robots[1].pos.y = 130;
		robots[1].rotation = 0;
		robots[2].pos.x = 130;
		robots[2].pos.y = 120;
		robots[2].rotation = 0;
		robots[3].pos.x = 130;
		robots[3].pos.y = 80;
		robots[3].rotation = 0;
		robots[4].pos.x = 130;
		robots[4].pos.y = 50;
		robots[4].rotation = 0;
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		robots[0].pos.x = 5;
		robots[0].pos.y = 90;
		robots[0].rotation = 90;
		robots[1].pos.x = 30;
		robots[1].pos.y = 100;
		robots[1].rotation = 0;
		robots[2].pos.x = 50;
		robots[2].pos.y = 65;
		robots[2].rotation = 0;
		robots[3].pos.x = 70;
		robots[3].pos.y = 40;
		robots[3].rotation = 0;
		robots[4].pos.x = 90;
		robots[4].pos.y = 130;
		robots[4].rotation = 0;
		break;
	case 12:
		break;
	}
}