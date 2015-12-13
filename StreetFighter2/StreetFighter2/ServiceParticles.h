#pragma once
#include "Service.h"
#include <list>

class Particle;
class IParticleFactory;
struct ParticleInfo;

class ServiceParticles : public Service
{
private:
	std::list<Particle*> particles;
	IParticleFactory* factory;

public:
	ServiceParticles();
	~ServiceParticles();

	bool Init();
	bool CleanUp();

	void SetParticleFactory(IParticleFactory* fact);
	void CreateParticle(const ParticleInfo& info);
	bool UpdateParticlesState();
	bool DrawParticles() const;
	bool DeleteInactiveParticles();
};

