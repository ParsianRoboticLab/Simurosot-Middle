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

void Soccer::init(std::thread* handle, std::ofstream* _logs) {
	m_handle = handle;
	logs = _logs;

}

void Soccer::updateWM(const WorldModel & _wm) {
	wm = _wm;
}
