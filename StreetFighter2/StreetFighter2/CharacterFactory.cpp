#include "CharacterFactory.h"
#include "Character.h"
#include "RyuKen.h"



CharacterFactory::CharacterFactory()
{
}


CharacterFactory::~CharacterFactory()
{
}

Character * CharacterFactory::CreateCharacter(CharacterType type)
{
	Character* result = nullptr;

	switch (type)
	{
	case CharacterType::RYU:
		result = new RyuKen(CharacterType::RYU);
		break;
	case CharacterType::HONDA:
		break;
	case CharacterType::BLANKA:
		break;
	case CharacterType::GUILE:
		break;
	case CharacterType::KEN:
		result = new RyuKen(CharacterType::KEN);
		break;
	case CharacterType::CHUNLI:
		break;
	case CharacterType::ZANGUIEF:
		break;
	case CharacterType::DALSHIM:
		break;
	case CharacterType::BALROG:
		break;
	case CharacterType::VEGA:
		break;
	case CharacterType::SAGAT:
		break;
	case CharacterType::BISON:
		break;
	default:
		break;
	}
	return result;
}
