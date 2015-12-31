#pragma once
#include "Entity.h"

class Scene : public Entity
{
protected:
	bool started;
public:
	Scene();
	~Scene();

	bool Start();
	bool Stop();
};

