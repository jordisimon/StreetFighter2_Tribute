#include "ServiceCollition.h"
#include "Defines.h"

#include "ServicesManager.h"
#include "ServiceRender.h"
#include "Collider.h"
#include "Collition.h"
#include "ICollitionListener.h"

using namespace std;

ServiceCollition::ServiceCollition() : drawColliders{ false }
{
}


ServiceCollition::~ServiceCollition()
{
}

bool ServiceCollition::Init()
{
	LOG("Init Collitions Service");

	return true;
}

bool ServiceCollition::CleanUp()
{
	LOG("CleanUp Collitions Service");

	for (list<Collition*>::iterator it = collitions.begin(); it != collitions.end(); ++it)
		RELEASE(*it);

	for (vector<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	return true;
}

Collider* ServiceCollition::CreateCollider(ColliderType t, const fRect& r, ICollitionListener* lis, const Color& col, bool act)
{
	Collider* collider = new Collider(t, r, lis, col, act);
	colliders.push_back(collider);
	return collider;
}

void ServiceCollition::ProcessCollitionYes(Collider* colA, Collider* colB)
{
	bool found = false;

	for (list<Collition*>::iterator it = collitions.begin(); it != collitions.end(); ++it)
	{
		if ((*it)->HasCollider(colA) && (*it)->HasCollider(colB))
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		if (colA->listener != nullptr)
			colA->listener->OnCollitionEnter(colA, colB);

		if (colB->listener != nullptr)
			colB->listener->OnCollitionEnter(colB, colA);

		collitions.push_back(new Collition(colA, colB));
	}
}

void ServiceCollition::ProcessCollitionNo(Collider * colA, Collider * colB)
{
	for (list<Collition*>::iterator it = collitions.begin(); it != collitions.end(); ++it)
	{
		if ((*it)->HasCollider(colA) && (*it)->HasCollider(colB))
		{
			if (colA->listener != nullptr)
				colA->listener->OnCollitionExit(colA, colB);

			if (colB->listener != nullptr)
				colB->listener->OnCollitionExit(colB, colA);

			RELEASE(*it);
			collitions.erase(it);
			break;
		}
	}
}

void ServiceCollition::CheckPair(Collider* colA, Collider* colB)
{
	//Optimization: If no collider changed, no collition changed
	if (!colA->changed && !colB->changed)
		return;

	if (!colA->active || !colB->active)
		return;

	
	if (colA->colliderRect.Intersects(colB->colliderRect))
	{
		ProcessCollitionYes(colA, colB);
	}
	else
	{
		ProcessCollitionNo(colA, colB);
	}
}

bool ServiceCollition::UpdateCollidersState()
{
	DeleteInactiveColliders();

	if (colliders.size() >= 2)
	{
		for (unsigned int i = 0; i <= colliders.size() - 2; ++i)
		{
			for (unsigned int j = i + 1; j <= colliders.size() - 1; ++j)
			{
				CheckPair(colliders[i], colliders[j]);
			}
		}
	}

	for (vector<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
	{
		(*it)->changed = false;	
	}

	return true;
}

bool ServiceCollition::DrawColliders() const
{
	if (drawColliders)
	{
		for (vector<Collider*>::const_iterator it = colliders.cbegin(); it != colliders.cend(); ++it)
		{
			if ((*it)->active && !(*it)->toDelete)
			{
				servicesManager->render->SetDrawColor((*it)->color);
				servicesManager->render->DrawRectLine((*it)->colliderRect);
			}
		}
	}
	return true;
}

bool ServiceCollition::DeleteInactiveColliders()
{
	for (list<Collition*>::iterator it = collitions.begin(); it != collitions.end(); /*nothing*/)
	{
		if ((*it)->HasToDeleteCollider())
		{
			RELEASE(*it);
			it = collitions.erase(it);
		}
		else
			++it;
	}

	for (vector<Collider*>::iterator it = colliders.begin(); it != colliders.end(); /*nothing*/)
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
