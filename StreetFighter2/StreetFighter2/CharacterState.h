#pragma once

struct CommandData;
class Collider;

class CharacterState
{
public:
	CharacterState();
	virtual ~CharacterState();

	virtual void OnEnter() {};
	virtual void OnExit() {};

	virtual CharacterState* ProcessInput(CommandData* commandData) { return nullptr; };
	virtual CharacterState* UpdateState() { return nullptr; };

	virtual void IfMovingForwardRecalculatePositionWithPressingSpeed() {};
	virtual CharacterState* DealHit(Collider* collider) { return nullptr; };
	virtual CharacterState* MatchFinished(int playerWin) { return nullptr; };
};

