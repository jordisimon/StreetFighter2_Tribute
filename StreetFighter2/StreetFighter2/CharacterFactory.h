#pragma once
#include "CharacterType.h"

class Character;

class CharacterFactory
{
public:
	CharacterFactory();
	~CharacterFactory();

	static Character* CreateCharacter(CharacterType type);
};

