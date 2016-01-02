#pragma once
#include "Point.h"
#include "Direction.h"

enum class ParticleType
{
	LIGHT_HADOKEN,
	MEDIUM_HADOKEN,
	HARD_HADOKEN,
	HIT_BLOCKED,
	P1_LHIT,
	P1_MHIT,
	P1_HHIT,
	P2_LHIT,
	P2_MHIT,
	P2_HHIT
};

struct ParticleInfo
{
	ParticleType type;
	fPoint position;
	Direction direction;
};
