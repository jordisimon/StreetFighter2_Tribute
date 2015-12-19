#pragma once

struct CommandData;

class State
{
public:
	State() {};
	virtual ~State() {};

	virtual void OnEnter() {};
	virtual void OnExit() {};

	virtual State* ProcessInput(CommandData* commandData) { return nullptr; };
	virtual State* UpdateState() { return nullptr; };
};

