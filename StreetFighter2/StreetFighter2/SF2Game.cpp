#include "SF2Game.h"
#include "Defines.h"
#include "ServiceParticles.h"
#include "ParticleFactory.h"

//Testing
#include "ServiceCommandManager.h"
#include "Match.h"

SF2Game::SF2Game()
{
	//testing
	match = new Match();
}


SF2Game::~SF2Game()
{
	//testing
	RELEASE(match);
}

bool SF2Game::Init()
{
	bool res = Game::Init();

	sParticles->SetParticleFactory(new ParticleFactory());

	//TODO: Load state
	res &= match->Init(config);
	res &= match->Start();

	return res;
}

bool SF2Game::CleanUp()
{
	match->Stop();
	match->CleanUp();

	Game::CleanUp();

	return true;
}

Entity::Result SF2Game::ProcessInput()
{
	Entity::Result result = Game::ProcessInput();

	if (result != Entity::Result::R_OK)
		return result;


	if (sCommands->CommandExit())
		return Entity::Result::R_EXIT;

	//TODO: Cascade processInput

	//Testing
	result = match->ProcessInput();

	return result;
}

Entity::Result SF2Game::UpdateState()
{
	Entity::Result result = Game::UpdateState();

	if (result != Entity::Result::R_OK)
		return result;

	//TODO: cascade Update State
	//Testing
	result = match->UpdateState();

	sCommands->Update();

	return result;
}

Entity::Result SF2Game::Draw()
{
	//TODO: cascade Draw()
	//Testing
	Entity::Result result = match->Draw();

	return result;
}

Game* CreateGame()
{
	return new SF2Game();
}
