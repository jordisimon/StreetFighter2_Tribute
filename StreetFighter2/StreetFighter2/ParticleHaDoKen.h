#pragma once
#include "Particle.h"
#include "ICollitionListener.h"

class Collider;

class ParticleHaDoKen :	public Particle, ICollitionListener
{
private:
	Collider* collider = nullptr;

public:
	enum class Type
	{
		LOW,
		MEDIUM,
		HARD
	};

	Animation endAnimation;
	fPoint speed;
	int damage;

	ParticleHaDoKen(fPoint pos, Direction dir, SDL_Texture* text, Type type);
	~ParticleHaDoKen();

	bool UpdateState();

	void OnCollitionEnter(Collider* colA, Collider* colB);
	void OnCollitionExit(Collider* colA, Collider* colB);
};

