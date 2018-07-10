#include "stdafx.h"
#include "../soccer.h"

void Soccer::Defense(Robot* robots, int size) {
	if (size < 1 || size > 2) {
		LOG(2 << "DEFENSE SIZE ERROR: " << size);
		return;
	}
	if (size == 1) {
		if (wm->getBall().vel.length() > 2 && wm->getBall().vel.getX() < 0) { // DIVE

		}
		else { // MOVE

		}
	}
	else { // size == 2
		if (wm->getBall().vel.length() > 2 && wm->getBall().vel.getX() < 0) { // DIVE

		}
		else { // MOVE

		}
	}
}