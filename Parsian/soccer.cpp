#include "stdafx.h"
#include "soccer.h"

std::mutex mutex;



Soccer::Soccer() {


	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&StartingTime);

	env = NULL;
	msg = new DataWrapper();
	wm = new CWorldModel();

	SYSTEMTIME st;
	GetLocalTime(&st);
	char* log_c = new char[100];
	sprintf(log_c, "logs/log-%d-%d-%d-%d-%d-%d.txt", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	log = new std::ofstream(log_c);

	// Initial Variables
	ballInOurSide = true;
	playonCounter = 0;
	playonFlag = false;
	debugs = new Logs();
	draws = new Draws();
	DetectionServer = new Server("192.168.43.105", 10040);
	PlotServer = new Server("192.168.43.105", 10030);
	LOG("START");

	// SKILLS
	posPID = new PID[ROBOT_COUNT];
	angPID = new PID[ROBOT_COUNT];
	last_pm = -1;

}

Soccer::~Soccer() {
	LOG("THE END");
	log->close();
	delete log;
	delete wm;
	delete DetectionServer;
}

void Soccer::init(const char* _teamName, bool isYellow) {
	teamName = _teamName;
	wm->teamColor = (isYellow) ? TColor::Yellow : TColor::Blue;
	LOG("INIT");
}

#define IFYELLOW(A,B) ((wm->teamColor == TColor::Yellow) ? (A) : (B))
void Soccer::updateGS(const PlayMode& pm) {
	LOG("UPDATEGS: " << pm);
	switch (pm) {
	case PM_PlayOn:
		wm->gs = GameMode::PlayOn; break;
	case PM_FreeBall_LeftTop:
		wm->gs = GameMode::FreeBall_LeftTop; break;
	case PM_FreeBall_LeftBot:
		wm->gs = GameMode::FreeBall_LeftBot; break;
	case PM_FreeBall_RightTop:
		wm->gs = GameMode::FreeBall_RightTop; break;
	case PM_FreeBall_RightBot:
		wm->gs = GameMode::FreeBall_RightBot; break;
	case PM_PlaceKick_Yellow:
		wm->gs = IFYELLOW(GameMode::OurKickOff, GameMode::OppKickOff); break;
	case PM_PlaceKick_Blue:
		wm->gs = IFYELLOW(GameMode::OppKickOff, GameMode::OurKickOff); break;
	case PM_PenaltyKick_Yellow:
		wm->gs = IFYELLOW(GameMode::OurPenaltyKick, GameMode::OppPenaltyKick); break;
	case PM_PenaltyKick_Blue:
		wm->gs = IFYELLOW(GameMode::OppPenaltyKick, GameMode::OurPenaltyKick); break;
	case PM_FreeKick_Yellow:
		wm->gs = IFYELLOW(GameMode::OurFreeKick, GameMode::OppFreeKick); break;
	case PM_FreeKick_Blue:
		wm->gs = IFYELLOW(GameMode::OppFreeKick, GameMode::OurFreeKick); break;
	case PM_GoalKick_Yellow:
		wm->gs = IFYELLOW(GameMode::OurGoalKick, GameMode::OppGoalKick); break;
	case PM_GoalKick_Blue:
		wm->gs = IFYELLOW(GameMode::OppGoalKick, GameMode::OurGoalKick); break;
	}
}

void Soccer::updateWM(Environment* _env) {
	LOG("UPDATE WM");
	env = _env;
	LOG("ENV COPIED");
	wm->update(_env);
	LOG("WM UPDATED");
	fillmsg();
	LOG("MSG FILLED");
	sendmsg();
	LOG("MSG SENT");
}

void Soccer::setFormerRobots(Robot* robots) {
	playonFlag = false;
	playonCounter = 0;
	LOG("FORMER");
	switch (wm->gs) {
	case GameMode::FreeBall_RightTop:
		robots[0].pos.x = 215;
		robots[0].pos.y = 100;
		robots[0].rotation = -90;
		robots[1].pos.x = 195;
		robots[1].pos.y = 150;
		robots[1].rotation = 180;
		robots[2].pos.x = 198;
		robots[2].pos.y = 80;
		robots[2].rotation = 180;
		robots[3].pos.x = 160;
		robots[3].pos.y = 80;
		robots[3].rotation = 180;
		robots[4].pos.x = 140;
		robots[4].pos.y = 50;
		robots[4].rotation = 180;
		break;
	case GameMode::FreeBall_RightBot:
		robots[0].pos.x = 215;
		robots[0].pos.y = 80;
		robots[0].rotation = -90;
		robots[1].pos.x = 195;
		robots[1].pos.y = 30;
		robots[1].rotation = 180;
		robots[2].pos.x = 198;
		robots[2].pos.y = 100;
		robots[2].rotation = 180;
		robots[3].pos.x = 160;
		robots[3].pos.y = 100;
		robots[3].rotation = 180;
		robots[4].pos.x = 140;
		robots[4].pos.y = 130;
		robots[4].rotation = 180;
		break;
	case GameMode::OurKickOff:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 180;
		robots[1].pos.y = 90;
		robots[1].rotation = 180;
		robots[2].pos.x = 120;
		robots[2].pos.y = 100;
		robots[2].rotation = 180;
		robots[3].pos.x = 125;
		robots[3].pos.y = 80;
		robots[3].rotation = 180;
		robots[4].pos.x = 95;
		robots[4].pos.y = 90;
		robots[4].rotation = 180;
		break;
	case GameMode::OppPenaltyKick:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 90;
		robots[1].pos.y = 160;
		robots[1].rotation = 180;
		robots[2].pos.x = 90;
		robots[2].pos.y = 120;
		robots[2].rotation = 180;
		robots[3].pos.x = 90;
		robots[3].pos.y = 80;
		robots[3].rotation = 180;
		robots[4].pos.x = 90;
		robots[4].pos.y = 50;
		robots[4].rotation = 180;

		break;
	case GameMode::OppFreeKick:
		// Goalie -> Center Of Goal
		robots[0].pos.x = 220 - 5; robots[0].pos.y = 90; robots[0].rotation = 90;
		// Others
		robots[1].pos.x = 220 - Field::penaltyAwidth - ROBOT_HALF_WIDTH;  robots[1].pos.y = Field::height / 2 + Field::penaltyAheight / 2 - ROBOT_HALF_WIDTH;  robots[1].rotation = 90;
		robots[2].pos.x = 220 - Field::penaltyAwidth - ROBOT_HALF_WIDTH;  robots[2].pos.y = Field::height / 2 + -Field::penaltyAheight / 2 + ROBOT_HALF_WIDTH; robots[2].rotation = 90;
		robots[3].pos.x = 220 - Field::penaltyBwidth + ROBOT_HALF_WIDTH;  robots[3].pos.y = Field::height / 2 + Field::penaltyBheight / 2 + ROBOT_HALF_WIDTH;  robots[3].rotation = 0;
		robots[4].pos.x = Field::penaltyBwidth - ROBOT_HALF_WIDTH;  robots[4].pos.y = Field::height / 2 + -Field::penaltyBheight / 2 - ROBOT_HALF_WIDTH; robots[4].rotation = 0;

		break;
	case GameMode::OurGoalKick:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 190;
		robots[1].pos.y = 100;
		robots[1].rotation = 180;
		robots[2].pos.x = 170;
		robots[2].pos.y = 65;
		robots[2].rotation = 180;
		robots[3].pos.x = 150;
		robots[3].pos.y = 40;
		robots[3].rotation = 180;
		robots[4].pos.x = 130;
		robots[4].pos.y = 130;
		robots[4].rotation = 180;

		break;

	default: /* For Case That We Don't Put Our Robots First */
		break;
	}

	LOG("FORMER END");
}

void Soccer::setLaterRobots(Robot* robots, const Robot* oppRobots, const Vector3D& _ball) {
	playonFlag = false;
	playonCounter = 0;
	LOG("LATER");
	switch (wm->gs) {
	case GameMode::FreeBall_LeftTop:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 165;
		robots[1].pos.y = 100;
		robots[1].rotation = 180;
		robots[2].pos.x = 130;
		robots[2].pos.y = 120;
		robots[2].rotation = 180;
		robots[3].pos.x = 95;
		robots[3].pos.y = 80;
		robots[3].rotation = 180;
		robots[4].pos.x = 85;
		robots[4].pos.y = 150;
		robots[4].rotation = 180;
		break;
	case GameMode::FreeBall_LeftBot:
		break;
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 165;
		robots[1].pos.y = 80;
		robots[1].rotation = 180;
		robots[2].pos.x = 130;
		robots[2].pos.y = 60;
		robots[2].rotation = 180;
		robots[3].pos.x = 95;
		robots[3].pos.y = 100;
		robots[3].rotation = 180;
		robots[4].pos.x = 85;
		robots[4].pos.y = 30;
		robots[4].rotation = 180;
		break;
	case GameMode::OppKickOff:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 190;
		robots[1].pos.y = 90;
		robots[1].rotation = 180;
		robots[2].pos.x = 150;
		robots[2].pos.y = 90;
		robots[2].rotation = 180;
		robots[3].pos.x = 130;
		robots[3].pos.y = 60;
		robots[3].rotation = 180;
		robots[4].pos.x = 130;
		robots[4].pos.y = 120;
		robots[4].rotation = 180;
		break;
	case GameMode::OurPenaltyKick:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 180;
		robots[1].pos.y = 90;
		robots[1].rotation = 180;
		robots[2].pos.x = 115;
		robots[2].pos.y = 110;
		robots[2].rotation = 180;
		robots[3].pos.x = 115;
		robots[3].pos.y = 70;
		robots[3].rotation = 180;
		robots[4].pos.x = 75;
		robots[4].pos.y = 90;
		robots[4].rotation = 180;
		break;

		break;
	case GameMode::OurFreeKick:
		robots[0].pos.x = 220 - 5;
		robots[0].pos.y = 90;
		robots[0].rotation = 90;
		robots[1].pos.x = 220 - 30;
		robots[1].pos.y = 80;
		robots[1].rotation = 0;
		robots[2].pos.x = 220 - 50;
		robots[2].pos.y = 180 - 65;
		robots[2].rotation = 0;
		robots[3].pos.x = 220 - 70;
		robots[3].pos.y = 180 - 40;
		robots[3].rotation = 0;
		robots[4].pos.x = 220 - 90;
		robots[4].pos.y = 180 - 130;
		robots[4].rotation = 0;
		break;
	case GameMode::OppGoalKick:
		robots[0].pos.x = 215;
		robots[0].pos.y = 90;
		robots[0].rotation = -90;
		robots[1].pos.x = 140;
		robots[1].pos.y = 50;
		robots[1].rotation = 180;
		robots[2].pos.x = 140;
		robots[2].pos.y = 130;
		robots[2].rotation = 180;
		robots[3].pos.x = 120;
		robots[3].pos.y = 60;
		robots[3].rotation = 180;
		robots[4].pos.x = 120;
		robots[4].pos.y = 90;
		robots[4].rotation = 180;
		break;

	default: /* For Case That We Put Our Robots First */
		break;
	}
	LOG("LATER END");
}

void Soccer::setBall(Vector3D* ball) {
	LOG("SET BALL");
	if (wm->gs == GameMode::OurGoalKick) {
#ifdef YELLOW
		ball->x = 10;
		ball->y = 70;
#else
		ball->x = 210;
		ball->y = 70;
#endif
	}
	LOG("SET BALL END");
}

/**
0) Goalie
1) Defense
2) Marks
3) Posiition
4) PlayMake
5) Support
*/

void Soccer::run(Robot* _robots) {
	LOG("RUN");
	robots = _robots;
	updateGS(PM_PlayOn);
	playon();
	LOG("END RUN");
}

void vec2D2vec2D(const rcsc::Vector2D& v1, Vector2D* v2) {
	v2->set_x(v1.getX());
	v2->set_y(v1.getY());
}
double lastX = 0;
double vx = 0;
void Soccer::fillmsg() {
	msg->Clear();
	header = msg->mutable_header();
	header->set_seq(wm->getLoop());
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;
	header->set_stamp_second(ElapsedMicroseconds.QuadPart / 1000000);
	header->set_stamp_nsecond(ElapsedMicroseconds.QuadPart % 1000000);

	detection = msg->mutable_detection();
	detection->set_frame_number(wm->getLoop());
	RBall * rball = detection->mutable_ball();
	rball->set_x(env->currentBall.pos.x);
	rball->set_y(env->currentBall.pos.y);
	rball->set_x(std::sqrtf(rball->x()*rball->x() + rball->y()*rball->y()));
	for (int i = 0; i < ROBOT_COUNT; i++) {
		RRobot* rb = detection->add_robots_blue();
		RRobot* ry = detection->add_robots_yellow();
#ifdef YELLOW
		rb->set_id(i);
		rb->set_x(env->opponent[i].pos.x);
		rb->set_y(env->opponent[i].pos.y);
		rb->set_ang(env->opponent[i].rotation);
		ry->set_id(i);
		ry->set_x(env->home[i].pos.x);
		ry->set_y(env->home[i].pos.y);
		ry->set_ang(env->home[i].rotation);
		LOG("RB: " << i << "X: " << env->opponent[i].pos.x);
#else
		ry->set_id(i);
		ry->set_x(env->opponent[i].pos.x);
		ry->set_y(env->opponent[i].pos.y);
		ry->set_ang(env->opponent[i].rotation);
		rb->set_id(i);
		rb->set_x(env->home[i].pos.x);
		rb->set_y(env->home[i].pos.y);
		rb->set_ang(env->home[i].rotation);
#endif // YELLOW
	}

	//msg->set_allocated_debugs(debugs);
	//msg->set_allocated_draws(draws);


	twm = msg->mutable_worldmodel();
	twm->set_blue(IFYELLOW(false, true));
	twm->set_gamestate(static_cast<GameState>(wm->gs));
	twm->set_mode("mahimode");
	MovingObject* moball = twm->mutable_ball();
	moball->set_id(0);
	moball->set_direction(0);
	moball->set_angulevelocity(0);
	vec2D2vec2D(wm->getBall().pos, moball->mutable_pos());
	vec2D2vec2D(wm->getBall().vel, moball->mutable_vel());
	vec2D2vec2D(wm->getBall().acc, moball->mutable_acc());
	for (int i = 0; i < ROBOT_COUNT; i++) {
		MovingObject* ourR = twm->add_our_robots();
		const CRobot& wor = wm->ourRobot(i);
		ourR->set_id(wor.id);
		ourR->set_angulevelocity(wor.w);
		ourR->set_direction(wor.th);
		vec2D2vec2D(wor.pos, ourR->mutable_pos());
		vec2D2vec2D(wor.vel, ourR->mutable_vel());
		vec2D2vec2D(wor.acc, ourR->mutable_acc());

		MovingObject* oppR = twm->add_opp_robots();
		const CRobot& wopr = wm->oppRobot(i);
		oppR->set_id(wopr.id);
		oppR->set_angulevelocity(wopr.w);
		oppR->set_direction(wopr.th);
		vec2D2vec2D(wopr.pos, oppR->mutable_pos());
		vec2D2vec2D(wopr.vel, oppR->mutable_vel());
		vec2D2vec2D(wopr.acc, oppR->mutable_acc());

	}


}

void Soccer::sendmsg() {
	std::string str;
	str.resize(twm->ByteSize());
	if (twm->SerializePartialToString(&str)) {
		LOG("STRSIZE: " << str.size() << strlen(str.c_str()));
		DetectionServer->send(str.c_str(), str.size());
	}
	else {

	}

	if (msg->SerializeToString(&str)) {
		LOG("STRSIZE: " << str.size());
		PlotServer->send(str.c_str(), str.size());
	}
	else {

	}


	debugs->clear_msgs();
	draws->clear_vectors();
	draws->clear_polygons();
	draws->clear_segments();
	draws->clear_texts();
	draws->clear_rects();
	draws->clear_circles();
}

void Soccer::setRobotVel(int id, double vel_tan, double w) {
	getRobotWheelPID(wm->ourRobot(id), w, vel_tan, robots[id].velocityRight, robots[id].velocityLeft);
}

void Soccer::setRobotAng(int id, double th) {
	#ifndef YELLOW
	th += 180;
	#endif // !YELLOW
	angPID[id].kp = 0.35;
	angPID[id].ki = 0;
	angPID[id].kd = 0.05;
	double diff{ wm->ourRobot(id).th - th };
	if (diff > 180)
		diff = -360 + diff;
	if (diff < -180)
		diff = 360 + diff;
	angPID[id].run(diff);
	setRobotVel(id, 0, -angPID[id].lastOut);
}

double Soccer::getRobotW(int id, double th)
{
	angPID[id].kp = 0.35;
	angPID[id].ki = 0;
	angPID[id].kd = 0.05;
	double diff{ wm->ourRobot(id).th - th };
	if (diff > 180)
		diff = -360 + diff;
	if (diff < -180)
		diff = 360 + diff;
	angPID[id].run(diff);
	return -1 * angPID[id].lastOut;
}

/*void Soccer::setRobotPos(int id, double pos_tan)
{
posPID[id].kp = 0.2;
posPID[id].ki = 0.0;
posPID[id].kd = 0.0;
double diff{ wm->ourRobot(1).pos.x - pos_tan };
if (fabs(diff) > 3) {
posPID[id].run(diff);
setRobotVel(1, -posPID[id].lastOut, 0);
}
else {
setRobotVel(1, 0, 0);
}
}*/

/*double Soccer::getRobotvel_tan(int id, double pos_tan)
{
posPID[id].kp = 0.2;
posPID[id].ki = 0.0;
posPID[id].kd = 0.0;
double diff{ wm->ourRobot(1).pos.x - pos_tan };
if (fabs(diff) > 3) {
posPID[id].run(diff);
return -1*posPID[id].lastOut;
}
else {
return 0;
}
}*/
