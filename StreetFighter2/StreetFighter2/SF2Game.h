#pragma once
#include "Game.h"

class CommandContext;

class SF2Game :	public Game
{
private:
	//Debug
	bool debug;
	float debugCameraSpeed;
	CommandContext* debugCommandContext;

public:
	SF2Game();
	~SF2Game();

	bool Init();
	bool CleanUp();

	bool UpdateInput() const;
	bool ProcessInput(CommandData* commandData);
};

