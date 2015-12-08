#include "ModuleConfig.h"
#include "Defines.h"

bool ModuleConfig::Init()
{
	LOG("Loading config --------------");
	ini.SetUnicode();
	
	return ini.LoadFile("config.ini") == SI_OK;
}


