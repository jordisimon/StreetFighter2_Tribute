#include "ParticleFactory.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "Particle.h"
#include "ParticleHaDoKen.h"

#define HADOKEN_SECTION "Particle_HaDoKen"

Particle * ParticleFactory::CreateParticle(const ParticleInfo& info)
{
	Particle* particle = nullptr;

	switch (info.type)
	{
	//Low HaDoKen
	case ParticleInfo::Type::LOW_HADOKEN:
		if (hadokenTexture == nullptr)
			hadokenTexture = servicesManager->textures->Load(HADOKEN_SECTION);

		particle = new ParticleHaDoKen(info.position, info.direction, hadokenTexture, ParticleHaDoKen::Type::LOW);
		break;

	//Medium HaDoKen
	case ParticleInfo::Type::MEDIUM_HADOKEN:
		if (hadokenTexture == nullptr)
			hadokenTexture = servicesManager->textures->Load(HADOKEN_SECTION);

		particle = new ParticleHaDoKen(info.position, info.direction, hadokenTexture, ParticleHaDoKen::Type::MEDIUM);
		break;

	//Hard HaDoKen
	case ParticleInfo::Type::HARD_HADOKEN:
		if (hadokenTexture == nullptr)
			hadokenTexture = servicesManager->textures->Load(HADOKEN_SECTION);

		particle = new ParticleHaDoKen(info.position, info.direction, hadokenTexture, ParticleHaDoKen::Type::HARD);
		break;
	}

	return particle;
}
