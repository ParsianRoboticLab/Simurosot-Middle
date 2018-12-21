#pragma once

#include <stdio.h>
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <windows.h>

#include "../util/base.h"
#include "../util/worldmodel.h"
#include "../util/knowledge.h"
#include "../util/server.h"
#include "../util/pid.h"

#include "../proto/messages_parsian_simurosot_data_wrapper.pb.h"

#define LOG(A) *log << A << std::endl 

#define DEBUG(MSG,LVL) {Log* m_marcomsg = debugs->add_msgs();\
m_marcomsg->set_level(LVL); \
m_macromsg->set_file(__FILE__); \
m_macromsg->set_line(__LINE__); \
m_macromsg->set_function(__FUNCTION__);\
}

#define DRAW_V(V,C) {Vec2D* v_macro = draws->add_vectors();\
v_macro->set_x(V.x()); \
v_macro->set_y(V.y()); \
Color* c_macro = v_macro->mutable_color(); \
c_macro->set_r(C.r()); \
c_macro->set_b(C.b()); \
c_macro->set_g(C.g()); \
c_macro->set_a(C.a()); \
}

#define DRAW_C(CI,SA,EA,R,F,CO) {Cir2D* c_macro = draws->add_circles();\
Vec2D* v_marcro = c_macro->mutable_center();\
v_macro->set_x(CI.center().x()); \
v_macro->set_y(CI.center().y()); \
c_macro->set_startAngle(SA); \
c_macro->set_endAngle(EA); \
c_macro->set_fill(F);\
Color* c_macro = v_macro->mutable_color(); \
c_macro->set_r(C.r()); \
c_macro->set_b(C.b()); \
c_macro->set_g(C.g()); \
c_macro->set_a(C.a()); \
}

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
	// Network
	Server* DetectionServer;
	Server* PlotServer;
	DataWrapper* msg;
	Header* header;
	Frame* detection;
	WorldModel* twm;
	void fillmsg();
	void sendmsg();
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;
	Logs* debugs;
	Draws* draws;
	
	// LOGS
	std::ofstream* log_env;
	std::ofstream* log_cmd;
	std::ofstream* log_wm;
	std::ofstream* log;

	// PLAYS
	void playon();

	bool ballInOurSide;
	int playonCounter;
	bool playonFlag;
	
	// PLANS
	void Defense(int ids[], int size);
	void Pos(int ids[], int size);
	
	// ROLES
	void PlayMake(int id);
	void Goalie(int id);

	// SKILLS //
	void setRobotVel(int id, double v_tan, double w);
	void setRobotAng(int id, double th);
	double getRobotW(int id, double th);
	
	/** GotoPoint **/
	void gotoPoint(int id, const rcsc::Vector2D&  targetPos, const rcsc::Vector2D& targetVel, double kp = 0.2);
	PID* posPID;
	PID* angPID;

	/** Spin **/
	void spin(int id, const rcsc::Vector2D&  targetPos, const double &targetVel);

	/** Kick **/
	void kick(int id, const rcsc::Vector2D&  targetPos);
	double pm_treshold;
	int last_pm;

};

