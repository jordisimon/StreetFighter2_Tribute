#pragma once
#include "Service.h"
class ServiceCommandManager : public Service
{
private:
	int debugCameraSpeed;

public:
	ServiceCommandManager() {};
	~ServiceCommandManager() {};

	bool Init(const Config& config);
	bool Update();

	bool CommandExit();

	bool P1Left();
	bool P1Right();
	bool P1Up();
	bool P1Down();
	bool P1UpLeft();
	bool P1UpRight();
	bool P1DownLeft();
	bool P1DownRight();

	bool P1LPunch();
};

