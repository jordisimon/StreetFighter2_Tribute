#include "ServiceParticles.h"
#include "Defines.h"
#include "IParticleFactory.h"
#include "Particle.h"

using namespace std;

ServiceParticles::ServiceParticles()
{
}

ServiceParticles::~ServiceParticles()
{
	RELEASE(factory);
}

bool ServiceParticles::Init()
{
	LOG("Init Particles Service");
	if (factory != nullptr)
		return factory->Init();

	return true;
}

bool ServiceParticles::CleanUp()
{
	LOG("CleanUp Particles Service");

	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); ++it)
		RELEASE(*it);

	if(factory != nullptr)
		factory->CleanUp();

	return true;
}

void ServiceParticles::SetParticleFactory(IParticleFactory * fact)
{
	factory = fact;
}

Particle* ServiceParticles::CreateParticle(const ParticleInfo& info)
{
	Particle* result = nullptr;

	if (factory != nullptr)
	{
		result = factory->CreateParticle(info);
		particles.push_back(result);
	}

	return result;
}

bool ServiceParticles::UpdateParticlesState()
{
	DeleteInactiveParticles();

	for (list<Particle*>::const_iterator it = particles.cbegin(); it != particles.cend(); ++it)
		(*it)->UpdateState();

	return true;
}

bool ServiceParticles::DrawParticles() const
{
	for (list<Particle*>::const_iterator it = particles.cbegin(); it != particles.cend(); ++it)
	{
		if (!(*it)->toDelete)
		{
			(*it)->Draw();
		}
	}

	return true;
}

bool ServiceParticles::DeleteInactiveParticles()
{
	for (list<Particle*>::iterator it = particles.begin(); it != particles.end(); /*nothing*/)
	{
		if ((*it)->toDelete)
		{
			RELEASE(*it);
			it = particles.erase(it);
		}
		else
			++it;
	}
	return true;
}
