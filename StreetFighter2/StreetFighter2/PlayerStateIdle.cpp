#include "PlayerStateIdle.h"
#include "Player.h"
#include "Game.h"
#include "ServiceRender.h"


PlayerStateIdle::PlayerStateIdle(Player* p): PlayerState(p)
{
}


PlayerStateIdle::~PlayerStateIdle()
{
}

void PlayerStateIdle::OnEnter()
{
	player->currentAnimation = &player->idle;
	player->currentAnimation->ResetAnimation();
}
