#include "Match.h"
#include "Defines.h"
#include "Player.h"
#include "Stage.h"
#include "Game.h"
#include "ServiceRender.h"
#include "ServiceParticles.h"
#include "ServiceCollition.h"

//Testing remove when done
#include "StageHonda.h"
#include "Ryu.h"
#include "Ken.h"


Match::Match()
{
	stage = new StageHonda();
	player1 = new Ryu();
	player2 = new Ken();
}


Match::~Match()
{
	RELEASE(player2);
	RELEASE(player1);
	RELEASE(stage);
}

bool Match::Init(const Config & config)
{
	bool ret;

	ret = stage->Init(config);
	ret = ret && player1->Init(config);
	ret = ret && player2->Init(config);

	game->sRender->SetCameraPostion(stage->camStart);
	player1->position = stage->p1StartPoint;
	player2->position = stage->p2StartPoint;
	player2->direction = Direction::LEFT;
	//ret = ret && 

	return ret;
}

bool Match::CleanUp()
{
	player2->CleanUp();
	player1->CleanUp();
	stage->CleanUp();
	return true;;
}

bool Match::Start()
{
	stage->Start();
	player1->Start();
	player2->Start();
	return true;
}

bool Match::Stop()
{
	player2->Stop();
	player1->Stop();
	stage->Stop();
	return true;
}

Entity::Result Match::ProcessInput()
{
	//TODO: delegate this to Match State
	//TODO: process own inputs (example Start pauses the match)
	player1->ProcessInput();
	//player2->ProcessInput();
	return Entity::Result::R_OK;
}

Entity::Result Match::UpdateState()
{
	//TODO: delegate this to Match State

	stage->UpdateState();
	player1->UpdateState();
	player2->UpdateState();
	game->sParticles->UpdateParticlesState();
	game->sCollitions->UpdateCollidersState();
	return Entity::Result::R_OK;
}

Entity::Result Match::Draw()
{
	stage->Draw();
	player1->Draw();
	player2->Draw();
	game->sParticles->DrawParticles();
	game->sCollitions->DrawColliders();
	/*
	hud->Draw();*/
	return Entity::Result::R_OK;
}
