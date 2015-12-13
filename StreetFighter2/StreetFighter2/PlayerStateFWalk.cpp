#include "PlayerStateFWalk.h"
#include "Player.h"


PlayerStateFWalk::PlayerStateFWalk(Player* p) : PlayerState(p)
{
}


PlayerStateFWalk::~PlayerStateFWalk()
{
}

void PlayerStateFWalk::OnEnter()
{
	player->currentAnimation = &player->fWalk;
	player->currentAnimation->ResetAnimation();
}
