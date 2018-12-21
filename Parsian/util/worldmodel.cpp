#include "stdafx.h"
#include "worldmodel.h"

CWorldModel::CWorldModel() {
	loop = 0;
	gs = GameMode::PlayOn;
#ifdef YELLOW
	teamColor = TColor::Yellow;
#else
	teamColor = TColor::Blue;
#endif // YELLOW

}

CWorldModel::~CWorldModel() {

}

void CWorldModel::update(const Environment* _env) {
	lastBall = ball;
	ball.pos.x =  _env->currentBall.pos.x - Field::width / 2;
	#ifndef YELLOW
	ball.pos.x *= -1;
	#endif
	ball.pos.y = -_env->currentBall.pos.y + Field::height / 2;
	ball.vel = ball.pos - lastBall.pos;
	ball.acc = ball.vel - lastBall.vel;
	for (int i = 0; i < ROBOT_COUNT; i++) {
		lastOur[i] = our[i];
		our[i].id = i;
		our[i].th = _env->home[i].rotation;
		our[i].w = _env->home[i].rotation - lastOur[i].th;
		if (our[i].w > 260)       our[i].w = our[i].w - 360;
		else if (our[i].w < -260) our[i].w = our[i].w + 360;
		our[i].pos.x = _env->home[i].pos.x - Field::width / 2;
		#ifndef YELLOW
		our[i].pos.x *= -1;
		#endif
		our[i].pos.y = -_env->home[i].pos.y + Field::height / 2;
		our[i].vel = our[i].pos - lastOur[i].pos;
		our[i].acc = our[i].vel - lastOur[i].vel;
		

		lastOpp[i] = opp[i];
		opp[i].id = i;
		opp[i].th = _env->opponent[i].rotation;
		opp[i].w = _env->opponent[i].rotation - lastOpp[i].th;
		if (opp[i].w > 260)       opp[i].w = opp[i].w - 360;
		else if (opp[i].w < -260) opp[i].w = opp[i].w + 360;
		opp[i].pos.x = _env->opponent[i].pos.x - Field::width / 2;
		#ifndef YELLOW
		opp[i].pos.x *= -1;
		#endif
		opp[i].pos.y = -_env->opponent[i].pos.y + Field::height / 2;
		opp[i].vel = opp[i].pos - lastOpp[i].pos;
		opp[i].acc = opp[i].vel - lastOpp[i].vel;
	}

	increaseLoop();
}