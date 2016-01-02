#include "ParticleFactory.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "Config.h"
#include "Particle.h"
#include "ParticleHaDoKen.h"
#include "ParticleHit.h"

#define PARTICLES_SECTION "Particles"

bool ParticleFactory::Init()
{
	particlesTexture = servicesManager->textures->Load(PARTICLES_SECTION);

	config->LoadAnimationCollider(hadokenRun, PARTICLES_SECTION, "hadoken");
	config->LoadAnimationCollider(hadokenEnd, PARTICLES_SECTION, "hadokenEnd");
	config->LoadAnimationCollider(hitBlocked, PARTICLES_SECTION, "hitBlocked");
	config->LoadAnimationCollider(p1lHit, PARTICLES_SECTION, "p1lHit");
	config->LoadAnimationCollider(p1mHit, PARTICLES_SECTION, "p1mHit");
	config->LoadAnimationCollider(p1hHit, PARTICLES_SECTION, "p1hHit");
	config->LoadAnimationCollider(p2lHit, PARTICLES_SECTION, "p2lHit");
	config->LoadAnimationCollider(p2mHit, PARTICLES_SECTION, "p2mHit");
	config->LoadAnimationCollider(p2hHit, PARTICLES_SECTION, "p2hHit");

	return true;
}

bool ParticleFactory::CleanUp()
{
	servicesManager->textures->Unload(particlesTexture);
	return true;
}

Particle * ParticleFactory::CreateParticle(const ParticleInfo& info)
{
	Particle* particle = nullptr;

	switch (info.type)
	{
	//Low HaDoKen
	case ParticleType::LIGHT_HADOKEN:
		particle = new ParticleHaDoKen(info.type, info.position, info.direction, particlesTexture, hadokenRun, hadokenEnd);
		break;

	//Medium HaDoKen
	case ParticleType::MEDIUM_HADOKEN:
		particle = new ParticleHaDoKen(info.type, info.position, info.direction, particlesTexture, hadokenRun, hadokenEnd);
		break;

	//Hard HaDoKen
	case ParticleType::HARD_HADOKEN:
		particle = new ParticleHaDoKen(info.type, info.position, info.direction, particlesTexture, hadokenRun, hadokenEnd);
		break;

	//Hit blocked
	case ParticleType::HIT_BLOCKED:
		particle = new ParticleHit(info.type, info.position, info.direction, particlesTexture, hitBlocked);
		break;

	//P1 Low Hit
	case ParticleType::P1_LHIT:
		particle = new ParticleHit(info.type, info.position, info.direction, particlesTexture, p1lHit);
		break;

	//P1 Medium Hit
	case ParticleType::P1_MHIT:
		particle = new ParticleHit(info.type, info.position, info.direction, particlesTexture, p1mHit);
		break;

	//P1 Hard Hit
	case ParticleType::P1_HHIT:
		particle = new ParticleHit(info.type, info.position, info.direction, particlesTexture, p1hHit);
		break;

	//P2 Low Hit
	case ParticleType::P2_LHIT:
		particle = new ParticleHit(info.type, info.position, info.direction, particlesTexture, p2lHit);
		break;

	//P2 Medium Hit
	case ParticleType::P2_MHIT:
		particle = new ParticleHit(info.type, info.position, info.direction, particlesTexture, p2mHit);
		break;

	//P2 Hard Hit
	case ParticleType::P2_HHIT:
		particle = new ParticleHit(info.type, info.position, info.direction, particlesTexture, p2hHit);
		break;
	}

	return particle;
}
