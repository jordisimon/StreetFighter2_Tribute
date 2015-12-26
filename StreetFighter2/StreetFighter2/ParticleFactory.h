#pragma once
#include "IParticleFactory.h"
#include "Point.h"
#include "Direction.h"

class Particle;
struct SDL_Texture;

struct ParticleInfo
{
	enum class Type
	{
		LOW_HADOKEN,
		MEDIUM_HADOKEN,
		HARD_HADOKEN
	};
	fPoint position;
	Direction direction;
	Type type;
};

class ParticleFactory : public IParticleFactory
{
private:
	SDL_Texture* hadokenTexture = nullptr;

public:
	ParticleFactory() {};
	~ParticleFactory() {};

	Particle* CreateParticle(const ParticleInfo& info);
};

