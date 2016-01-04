#pragma once
#include "Service.h"
#include <list>

class Particle;
class IParticleFactory;
struct ParticleInfo; //To be defined in Game specific implementation

class ServiceParticles : public Service
{
private:
	std::list<Particle*> particles;
	IParticleFactory* factory = nullptr;

public:
	ServiceParticles();
	~ServiceParticles();

	bool Init();
	bool CleanUp();

	void SetParticleFactory(IParticleFactory* fact);
	Particle* CreateParticle(const ParticleInfo& info);
	bool UpdateParticlesState();
	bool DrawParticles() const;
	bool DeleteInactiveParticles();
};

