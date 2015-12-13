#include "ParticleHaDoKen.h"
#include "Defines.h"
#include "Config.h"
#include "Game.h"
#include "ServiceTextures.h"
#include "ServiceCollition.h"
#include "Color.h"
#include "Collider.h"

#define CONFIG_SECTION "Particle_HaDoKen"


ParticleHaDoKen::ParticleHaDoKen(iPoint pos, Direction dir, SDL_Texture* text, Type type) : Particle(pos, dir, text)
{
	timeout = SDL_GetTicks() + 1000; 

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
	game->config.LoadAnimation(*animation, CONFIG_SECTION, "hdk");
	game->config.LoadAnimation(endAnimation, CONFIG_SECTION, "hdkEnd");
	endAnimation.loop = false;

	collider = game->sCollitions->CreateCollider(animation->GetFrame().rect, this, Color(Color::Predefined::RED));
	collider->SetPosition(animation->GetFrame().GetBlitPosition(position, direction));
}


ParticleHaDoKen::~ParticleHaDoKen()
{
}

bool ParticleHaDoKen::UpdateState()
{
	if (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout))
	{
		position += speed;
		animation->UpdateCurrentFrame();
		collider->SetPosition(animation->GetFrame().GetBlitPosition(position, direction));
	}
	else
	{
		animation = &endAnimation;
		animation->UpdateCurrentFrame();

		toDelete = animation->HasFinished();
	}
	return true;
}
