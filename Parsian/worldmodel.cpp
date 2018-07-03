#include "stdafx.h"
#include "worldmodel.h"

CWorldModel::CWorldModel() {
	loop = 0;
	gs = GameMode::PlayOn;
	teamColor = TColor::Yellow;

}

CWorldModel::~CWorldModel() {

}

void CWorldModel::update(const Environment* _env) {
	increaseLoop();
}