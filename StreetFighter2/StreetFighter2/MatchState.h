#pragma once

struct CommandData;
class SceneMatch;

class MatchState
{
protected:
	SceneMatch* scene = nullptr;

public:
	MatchState(SceneMatch* s) : scene{ s } {};
	~MatchState() {};

	virtual void OnEnter() {};
	virtual void OnExit() {};

	virtual MatchState* ProcessInput(CommandData* commandData) { return nullptr; };
	virtual MatchState* UpdateState() { return nullptr; };
};

