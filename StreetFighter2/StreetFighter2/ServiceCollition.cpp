#include "ServiceCollition.h"
#include "Defines.h"
#include "Game.h"
#include "ServiceRender.h"
#include "Collider.h"

using namespace std;

ServiceCollition::ServiceCollition()
{
}


ServiceCollition::~ServiceCollition()
{
}

bool ServiceCollition::Init(const Config & config)
{
	LOG("Init Collitions Service");
	debug = game->debug;

	return true;
}

bool ServiceCollition::CleanUp()
{
	LOG("CleanUp Collitions Service");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	return true;
}

Collider* ServiceCollition::CreateCollider(const SDL_Rect& r, ICollitionListener* lis, const Color& col)
{
	Collider* collider = new Collider(r, lis, col);
	colliders.push_back(collider);
	return collider;
}

bool ServiceCollition::UpdateCollidersState()
{
	return false;
}

bool ServiceCollition::DrawColliders() const
{
	if (debug)
	{
		for (list<Collider*>::const_iterator it = colliders.cbegin(); it != colliders.cend(); ++it)
		{
			if (!(*it)->toDelete)
			{
				game->sRender->SetDrawColor((*it)->color);
				game->sRender->DrawRect(&(*it)->colliderRect);
			}
		}

		return true;
	}
	return true;
}

bool ServiceCollition::DeleteInactiveColliders()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); /*nothing*/)
	{
		if ((*it)->toDelete)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}
	return true;
}
