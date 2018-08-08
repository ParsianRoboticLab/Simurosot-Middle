#include "stdafx.h"
#include "../soccer.h"


void Soccer::PlayMake(int id) {
	kick(id, Field::oppGoal());
}