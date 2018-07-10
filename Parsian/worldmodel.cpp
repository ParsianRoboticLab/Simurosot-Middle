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
	ball.pos.x = _env->currentBall.pos.x;
	ball.pos.y = _env->currentBall.pos.y;
	ball.vel.x = _env->currentBall.pos.x - _env->lastBall.pos.x;
	ball.vel.y = _env->currentBall.pos.y - _env->lastBall.pos.y;
	ball.acc.x = ball.vel.x - lastBall.vel.x;
	ball.acc.y = ball.vel.y - lastBall.vel.y;
	for (int i = 0; i < ROBOT_COUNT; i++) {
		lastOur[i] = our[i];
		our[i].id = i;
		our[i].th = _env->home[i].rotation;
		our[i].w = _env->home[i].rotation - lastOur[i].th;
		our[i].pos.x = _env->home[i].pos.x;
		our[i].pos.y = _env->home[i].pos.x;
		our[i].vel = our[i].pos - lastOur[i].pos;
		our[i].acc = our[i].vel - lastOur[i].vel;
		

		lastOpp[i] = opp[i];
		opp[i].id = i;
		opp[i].th = _env->opponent[i].rotation;
		opp[i].w = _env->opponent[i].rotation - lastOpp[i].th;
		opp[i].pos.x = _env->opponent[i].pos.x;
		opp[i].pos.y = _env->opponent[i].pos.x;
		opp[i].vel = opp[i].pos - lastOpp[i].pos;
		opp[i].acc = opp[i].vel - lastOpp[i].vel;
	}

	increaseLoop();
}