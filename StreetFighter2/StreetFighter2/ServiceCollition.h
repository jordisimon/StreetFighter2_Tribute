#pragma once
#include "Service.h"
#include <vector>
#include <list>
#include "Rect.h"

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

	Collider* CreateCollider(ColliderType t, const fRect& r, ICollitionListener* lis, const Color& col, bool act = true);
	bool UpdateCollidersState();
	bool DrawColliders() const;
	bool DeleteInactiveColliders();
};

