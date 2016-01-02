#pragma once
#include "CharacterSpecialAttack.h"

enum class RyuKenSpecialAttackType
{
	L_HADOKEN,
	M_HADOKEN,
	H_HADOKEN,
	L_SHORYUKEN,
	M_SHORYUKEN,
	H_SHORYUKEN,
	L_KYAKU,
	M_KYAKU,
	H_KYAKU
};

class RyuKenSpecialAttack : public CharacterSpecialAttack
{
public:
	RyuKenSpecialAttack(RyuKenSpecialAttackType t) : type{ t } {}
	RyuKenSpecialAttackType type;
};
