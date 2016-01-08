#pragma once
#include "CharacterStats.h"

struct PlayerStats
{
	unsigned int score = 0;
	unsigned int wins = 0;
	unsigned int loses = 0;
	unsigned int draws = 0;
	unsigned int SPKO = 0;

	CharacterStats Ryu;
	CharacterStats Honda;
	CharacterStats Blanka;
	CharacterStats Guile;
	CharacterStats Ken;
	CharacterStats Chunli;
	CharacterStats Zanguief;
	CharacterStats Dalshim;
};
