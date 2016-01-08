#pragma once

enum class AttackType
{
	L_PUNCH,
	M_PUNCH,
	H_PUNCH,
	F_L_PUNCH,
	F_M_PUNCH,
	F_H_PUNCH,
	C_L_PUNCH,
	C_M_PUNCH,
	C_H_PUNCH,
	L_KICK,
	M_KICK,
	H_KICK,
	F_L_KICK,
	F_M_KICK,
	F_H_KICK,
	C_L_KICK,
	C_M_KICK,
	C_H_KICK,
	J_L_PUNCH,
	J_M_PUNCH,
	J_H_PUNCH,
	F_J_L_PUNCH,
	F_J_M_PUNCH,
	F_J_H_PUNCH,
	J_L_KICK,
	J_M_KICK,
	J_H_KICK,
	F_J_L_KICK,
	F_J_M_KICK,
	F_J_H_KICK,
	SPECIAL
};

enum class AttackStrength
{
	NONE,
	LIGHT,
	MEDIUM,
	HARD
};

struct AttackInfo
{
	AttackInfo() : strength{ AttackStrength::NONE }, damage { 0 }, backMovement{ 0.0f }, backSpeed{ 0.0f } {}

	AttackStrength strength;
	AttackType type;
	int damage;
	float backMovement;
	float backSpeed;
};
