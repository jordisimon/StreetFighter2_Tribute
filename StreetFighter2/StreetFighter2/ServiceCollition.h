#pragma once
#include "Service.h"
#include <list>

struct SDL_Rect;
class Collider;
class ICollitionListener;
class Color;

class ServiceCollition : public Service
{
private:
	bool debug;
	std::list<Collider*> colliders;

public:
	ServiceCollition();
	~ServiceCollition();

	bool Init(const Config& config);
	bool CleanUp();

	Collider* CreateCollider(const SDL_Rect& r, ICollitionListener* lis, const Color& col);
	bool UpdateCollidersState();
	bool DrawColliders() const;
	bool DeleteInactiveColliders();
};

