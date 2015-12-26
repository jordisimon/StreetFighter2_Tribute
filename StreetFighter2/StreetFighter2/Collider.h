#pragma once
#include "Color.h"
#include "Point.h"
#include "Rect.h"

class ICollitionListener;
enum class ColliderType; //To be defined in Game specific implementation

class Collider
{
public:
	Collider(ColliderType t, const fRect& r, ICollitionListener* lis, const Color& col, bool act = true);
	virtual ~Collider();

	ColliderType type;
	fRect colliderRect;
	ICollitionListener* listener = nullptr;
	Color color;
	bool active;
	bool changed;	
	bool toDelete;
	
	void SetRect(const fRect& rect);
	void SetPosition(const fPoint& pos);
};

