#pragma once

class State
{
public:
	State() {};
	virtual ~State() {};

	virtual void OnEnter() {};
	virtual void OnExit() {};

	virtual State* ProcessInput() { return nullptr; };
	virtual State* UpdateState() { return nullptr; };
};

