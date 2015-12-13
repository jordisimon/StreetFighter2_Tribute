#include "PlayerState.h"
#include "Player.h"

PlayerState::PlayerState(Player* p): player(p)
{
}


PlayerState::~PlayerState()
{
}

State * PlayerState::UpdateState()
{
	player->currentAnimation->UpdateCurrentFrame();
	return nullptr;
}
