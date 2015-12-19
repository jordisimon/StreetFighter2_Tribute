#include "ParticleHaDoKen.h"
#include "Defines.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceCollition.h"
#include "Color.h"
#include "Collider.h"
#include "ColliderType.h"

#include "Config.h"

#define CONFIG_SECTION "Particle_HaDoKen"


ParticleHaDoKen::ParticleHaDoKen(iPoint pos, Direction dir, SDL_Texture* text, Type type) : Particle(pos, dir, text)
{
	speed.y = 0;

	switch (type)
	{
	case ParticleHaDoKen::Type::LOW:
		speed.x = 1;
		damage = 10;
		break;
	case ParticleHaDoKen::Type::MEDIUM:
		speed.x = 2;
		damage = 20;
		break;
	case ParticleHaDoKen::Type::HARD:
		speed.x = 3;
		damage = 30;
		break;
	default:
		break;
	}

	if (direction == Direction::LEFT)
		speed.x *= -1;

	animation = new Animation();
	config->LoadAnimation(*animation, CONFIG_SECTION, "hdk");
	config->LoadAnimation(endAnimation, CONFIG_SECTION, "hdkEnd");
	endAnimation.loop = false;

	collider = servicesManager->collitions->CreateCollider(ColliderType::PARTICLE, animation->GetFrame().rect, this, Color(Color::Predefined::RED));
	collider->SetPosition(animation->GetFrame().GetBlitPosition(position, direction));
}


ParticleHaDoKen::~ParticleHaDoKen()
{
}

bool ParticleHaDoKen::UpdateState()
{
	position += speed;
	animation->UpdateCurrentFrame();
	collider->SetPosition(animation->GetFrame().GetBlitPosition(position, direction));

	return true;
}

void ParticleHaDoKen::OnCollitionEnter(Collider * colA, Collider * colB)
{
}

void ParticleHaDoKen::OnCollitionExit(Collider * colA, Collider * colB)
{
	if (colB->type == ColliderType::SCENE_BOX)
	{
		colA->toDelete = true;
		toDelete = true;
	}
}
