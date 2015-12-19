#pragma once
#include "StageType.h"

class Stage;

class StageFactory
{
public:
	StageFactory();
	~StageFactory();

	static Stage* CreateStage(StageType type);
};

