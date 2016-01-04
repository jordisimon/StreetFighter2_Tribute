#pragma once
#include "IParticleFactory.h"
#include "Point.h"
#include "Direction.h"
#include "AnimationCollider.h"
#include "ParticleInfo.h"

class Particle;
struct SDL_Texture;

class ParticleFactory : public IParticleFactory
{
private:
	SDL_Texture* particlesTexture = nullptr;
	AnimationCollider hadokenRun;
	AnimationCollider hadokenEnd;
	AnimationCollider hitBlocked;
	AnimationCollider p1lHit;
	AnimationCollider p1mHit;
	AnimationCollider p1hHit;
	AnimationCollider p2lHit;
	AnimationCollider p2mHit;
	AnimationCollider p2hHit;
	AnimationCollider stars;
	AnimationCollider ducks;

public:
	ParticleFactory() {};
	~ParticleFactory() {};

	bool Init();
	bool CleanUp();
	Particle* CreateParticle(const ParticleInfo& info);
};

