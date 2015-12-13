#pragma once
#include "Particle.h"
#include "ICollitionListener.h"

class Collider;

class ParticleHaDoKen :	public Particle, ICollitionListener
{
private:
	unsigned int timeout;
	Collider* collider;

public:
	enum class Type
	{
		LOW,
		MEDIUM,
		HARD
	};

	Animation endAnimation;
	iPoint speed;
	int damage;

	ParticleHaDoKen(iPoint pos, Direction dir, SDL_Texture* text, Type type);
	~ParticleHaDoKen();

	bool UpdateState();

	void OnCollitionEnter(Collider* colA, Collider* colB) {};
	void OnCollitionExit(Collider* colA, Collider* colB) {};
};

