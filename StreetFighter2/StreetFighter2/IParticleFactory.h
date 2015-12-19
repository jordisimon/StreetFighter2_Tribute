#pragma once

class Particle;
struct ParticleInfo; //To be defined in Game specific implementation

class IParticleFactory
{
public:
	virtual Particle* CreateParticle(const ParticleInfo& info) = 0;
};
