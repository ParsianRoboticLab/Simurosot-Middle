#include "stdafx.h"
#include "soccer.h"

std::mutex mutex;

Soccer::Soccer() {
	env = NULL;
	wm = new CWorldModel();

	char* log_c = new char[100];
	sprintf(log_c,"log-%d-%d-%d-%d-%d-%d.txt",1,2,3,4,5,6);
	log = new std::ofstream(log_c);

}

Soccer::~Soccer() {
	log->close();
	delete log;
	delete wm;
}

void Soccer::init(const char* _teamName, bool isYellow) {
	teamName = _teamName;
	wm->teamColor = (isYellow) ? TColor::Yellow : TColor::Blue;
}

#define IFYELLOW(A,B) ((wm->teamColor == TColor::Yellow) ? (A) : (B))
void Soccer::updateGS(const PlayMode& pm) {
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
	env = _env;
	wm->update(_env);
	// TODO: update WM
}
#undef IFYELLOW(A,B)

void Soccer::setFormerRobots(Robot* robots) {
	switch (wm->gs) {
	case GameMode::FreeBall_LeftTop:
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
	case GameMode::FreeBall_LeftBot:
		break;

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
	case GameMode::OurKickOff:
		break;
	case GameMode::OppPenaltyKick:
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

		break;
	case GameMode::OppFreeKick:
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
	case GameMode::OurGoalKick:
		break;

	default: /* For Case That We Don't Put Our Robots First */
		break;
	}
}

void Soccer::setLaterRobots(Robot* robots, const Robot* oppRobots, const Vector3D& _ball) {
	switch (wm->gs) {
	case GameMode::FreeBall_RightTop:
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
	case GameMode::FreeBall_RightBot:
		break;

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
	case GameMode::OppKickOff:
		break;
	case GameMode::OurPenaltyKick:
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

		break;
	case GameMode::OurFreeKick:
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
	case GameMode::OppGoalKick:
		break;

	default: /* For Case That We Put Our Robots First */
		break;
	}
}

void Soccer::setBall(Vector3D* ball) {
	if (wm->gs == GameMode::OurGoalKick) {
		ball->x = 10;
		ball->y = 70;
	}
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
	robots = _robots;
	switch (wm->gs) {
	case GameMode::PlayOn:
		playon();
		break;
	case GameMode::FreeBall_LeftTop:
		freeballLT();
		break;
	case GameMode::FreeBall_LeftBot:
		freeballLB();
		break;
	case GameMode::FreeBall_RightTop:
		freeballRT();
		break;
	case GameMode::FreeBall_RightBot:
		freeballRB();
		break;
	case GameMode::OurKickOff:
		ourKO();
		break;
	case GameMode::OppKickOff:
		oppKO();
		break;
	case GameMode::OurPenaltyKick:
		ourPK();
		break;
	case GameMode::OppPenaltyKick:
		oppPK();
		break;
	case GameMode::OurFreeKick:
		ourFK();
		break;
	case GameMode::OppFreeKick:
		oppFK();
		break;
	case GameMode::OurGoalKick:
		ourGK();
		break;
	case GameMode::OppGoalKick:
		oppGK();
		break;
	}
}