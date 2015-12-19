#pragma once
#include "Service.h"
#include <vector>
#include <list>

struct SDL_Rect;
class Collider;
class Collition;
class ICollitionListener;
class Color;
enum class ColliderType; //To be defined in Game specific implementation

class ServiceCollition : public Service
{
private:
	std::vector<Collider*> colliders;
	std::list<Collition*> collitions;

	void ProcessCollitionYes(Collider* colA, Collider* colB);
	void ProcessCollitionNo(Collider* colA, Collider* colB);
	void CheckPair(Collider* colA, Collider* colB);

public:
	bool drawCollitions;

	ServiceCollition();
	~ServiceCollition();

	bool Init();
	bool CleanUp();

	Collider* CreateCollider(ColliderType t, const SDL_Rect& r, ICollitionListener* lis, const Color& col);
	bool UpdateCollidersState();
	bool DrawColliders() const;
	bool DeleteInactiveColliders();
};

