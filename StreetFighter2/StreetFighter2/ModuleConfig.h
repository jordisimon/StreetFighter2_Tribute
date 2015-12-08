#pragma once
#include "Module.h"
#include "SimpleIni.h"

class ModuleConfig : public Module
{
private:
	CSimpleIniA ini;

public:
	ModuleConfig(bool active = true) : Module(active) {};
	~ModuleConfig() {}

	bool Init();
};

