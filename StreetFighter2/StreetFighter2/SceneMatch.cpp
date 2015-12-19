#include "SceneMatch.h"
#include "Defines.h"
#include "Character.h"
#include "SceneMatchGUI.h"
#include "Stage.h"
#include "ServicesManager.h"
#include "ServiceAudio.h"
#include "ServiceCommandManager.h"
#include "ServiceRender.h"
#include "ServiceParticles.h"
#include "ServiceCollition.h"
#include "CharacterFactory.h"
#include "StageFactory.h"
#include "MatchStateIntro.h"
#include "CommandContext.h"

int SceneMatch::pauseFx = -1;
int SceneMatch::roundFx = -1;
int SceneMatch::oneFx = -1;
int SceneMatch::twoFx = -1;
int SceneMatch::threeFx = -1;
int SceneMatch::fourFx = -1;
int SceneMatch::fightFx = -1;

SceneMatch::SceneMatch(const SceneMatchInfo& sceneInfo) : timer{ 1000, true }, paused{ false }, roundNumber{ 0 }
{
	GUI = new SceneMatchGUI();
	commandContextFight = servicesManager->commands->Load("Match_Command_Context");
	commandContextPause = servicesManager->commands->Load("Pause_Command_Context");
	currentState = new MatchStateIntro(this);
	stage = StageFactory::CreateStage(sceneInfo.stageType);
	player1 = CharacterFactory::CreateCharacter(sceneInfo.player1Type);
	player2 = CharacterFactory::CreateCharacter(sceneInfo.player2Type);
	timeLimit = sceneInfo.timeLimit;

	if (pauseFx == -1) pauseFx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Pause.ogg");
	if (roundFx == -1) roundFx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Voices\\Match\\Round.ogg");
	if (oneFx == -1) oneFx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Voices\\Match\\One.ogg");
	if (twoFx == -1) twoFx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Voices\\Match\\Two.ogg");
	if (threeFx == -1) threeFx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Voices\\Match\\Three.ogg");
	if (fourFx == -1) fourFx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Voices\\Match\\Four.ogg");
	if (fightFx == -1) fightFx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Voices\\Match\\Fight.ogg");
}


SceneMatch::~SceneMatch()
{	
	RELEASE(player2);
	RELEASE(player1);
	RELEASE(stage);
	RELEASE(currentState);
	RELEASE(GUI);
}

bool SceneMatch::Init()
{
	bool ret;

	time = 99;
	GUI->scene = this;
	commandContextFight->AddCommandListener(this);
	commandContextPause->AddCommandListener(this);

	ret = stage->Init();
	ret = ret && player1->Init();
	ret = ret && player2->Init();

	servicesManager->render->SetCameraPostion(stage->camStart);
	player1->position = stage->p1StartPoint;
	player2->position = stage->p2StartPoint;
	player2->direction = Direction::LEFT;

	player1->playerNumber = 1;
	player2->playerNumber = 2;

	return ret;
}

bool SceneMatch::CleanUp()
{
	commandContextFight->RemoveCommandListener(this);
	commandContextPause->RemoveCommandListener(this);

	player2->CleanUp();
	player1->CleanUp();
	stage->CleanUp();

	return true;;
}

bool SceneMatch::Start()
{
	currentState->OnEnter();
	stage->Start();
	player1->Start();
	player2->Start();
	return true;
}

bool SceneMatch::Stop()
{
	player2->Stop();
	player1->Stop();
	stage->Stop();
	return true;
}

bool SceneMatch::ProcessInput(CommandData* commandData)
{
	State* newState = currentState->ProcessInput(commandData);
	if (newState != nullptr)
	{
		currentState->OnExit();
		RELEASE(currentState);
		currentState = newState;
		newState->OnEnter();
	}

	return true;
}

Entity::Result SceneMatch::UpdateState()
{
	State* newState = currentState->UpdateState();

	if (newState != nullptr)
	{
		currentState->OnExit();
		RELEASE(currentState);
		currentState = newState;
		newState->OnEnter();
	}

	return Entity::Result::R_OK;
}

Entity::Result SceneMatch::Draw()
{
	stage->Draw();
	player1->Draw();
	player2->Draw();
	servicesManager->particles->DrawParticles();
	servicesManager->collitions->DrawColliders();
	GUI->Draw();
	DrawGUI();
	return Entity::Result::R_OK;
}

void SceneMatch::DrawGUI()
{
}
