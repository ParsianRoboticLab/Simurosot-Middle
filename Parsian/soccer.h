#pragma once

#include <stdio.h>
#include <stdlib.h> 
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>
#include "base.h"
#include <windows.h>
#include "worldmodel.h"
#include "knowledge.h"
#include "proto\messages_parsian_simurosot_data_wrapper.pb.h"
#include "server.h"
#include "util/bangbang.h"
#include "util/pid.h"
#include "toml11/toml.hpp"

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

struct dynamic_reconfigure_values
{
	//[GoalKeeper]
	int goalie_id;
	//[PlayMake]
	float playmake_change_cost;
	//[Defense]
	float critical_mode;
	float non_threat_mode;
	int critical_defense_num;
	int non_threat_defense_num;
	int normal_defense_num;
};

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
	void dynamic_reconfigure();
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
	int playonCounter;
	bool playonFlag;
	void Defense(int ids[], int size);
	void Pos(int ids[], int size);
	void PlayMake(int id);
	
	void Goalie(int id);

	// SKILLS //
	void setRobotVel(int id, double v_tan, double w);
	void setRobotAng(int id, double th);
	double getRobotW(int id, double th);
	//void setRobotPos(int id, double pos_tan);
	//double getRobotvel_tan(int id, double pos_tan);
	void gotoPoint(int id, const rcsc::Vector2D&  targetPos, const rcsc::Vector2D& targetVel, double kp = 0.2);
	/** GotoPoint **/
	PID* posPID;
	PID* angPID;

	void spin(int id, const rcsc::Vector2D&  targetPos, const double &targetVel);
	/** Spin **/

	void kick(int id, const rcsc::Vector2D&  targetPos);
	/** Kick **/
	double pm_treshold;
	int last_pm;

	//dynamic reconfigure
	dynamic_reconfigure_values conf_vals;
};

