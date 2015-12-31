#pragma once

class Particle;
struct ParticleInfo; //To be defined in Game specific implementation

class IParticleFactory
{
public:
	virtual ~IParticleFactory() {};

	virtual bool Init() = 0;
	virtual bool CleanUp() = 0;
	virtual Particle* CreateParticle(const ParticleInfo& info) = 0;
};
