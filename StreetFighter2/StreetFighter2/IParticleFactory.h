#pragma once

class Particle;
struct ParticleInfo;

class IParticleFactory
{
public:
	virtual Particle* CreateParticle(const ParticleInfo& info) = 0;
};
