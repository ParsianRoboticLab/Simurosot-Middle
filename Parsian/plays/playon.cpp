#include "stdafx.h"
#include "../soccer.h"

void Soccer::playon() {
    Goalie(env);
	Position(&robots[1], 0, 0);
	Position(&robots[2], 10, 10);
	Position(&robots[3], 20, 20);
	Position(&robots[4], 30, 30);

}