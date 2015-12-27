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
	player1->match = this;
	player2 = CharacterFactory::CreateCharacter(sceneInfo.player2Type);
	player2->match = this;
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
	//Init GUI AFTER players (because it needs player id)
	GUI->Init();

	camPosition = stage->camStart;
	SetCamPosition();
	player1->position = stage->p1StartPoint;
	player2->position = stage->p2StartPoint;
	player2->direction = Direction::LEFT;

	player1->playerNumber = 1;
	player2->playerNumber = 2;

	scene25Percent = servicesManager->render->GetCamera().w / 4;
	scene50Percent = servicesManager->render->GetCamera().w / 2;
	scene75Percent = servicesManager->render->GetCamera().w / 4 * 3;

	return ret;
}

bool SceneMatch::CleanUp()
{
	commandContextFight->RemoveCommandListener(this);
	commandContextPause->RemoveCommandListener(this);

	player2->CleanUp();
	player1->CleanUp();
	stage->CleanUp();
	GUI->CleanUp();
	return true;;
}

bool SceneMatch::Start()
{
	GUI->Start();
	stage->Start();
	player1->Start();
	player2->Start();
	currentState->OnEnter();
	
	return true;
}

bool SceneMatch::Stop()
{
	player2->Stop();
	player1->Stop();
	stage->Stop();
	GUI->Stop();
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
	player2->Draw();
	player1->Draw(); //Player1 painted over player 2
	servicesManager->particles->DrawParticles();
	servicesManager->collitions->DrawColliders();
	GUI->Draw();
	return Entity::Result::R_OK;
}

int SceneMatch::GetGroundPosition()
{
	return stage->groundLevel;
}

float SceneMatch::GetMinXPosition()
{
	return servicesManager->render->GetCamera().x;
}

float SceneMatch::GetMaxXPosition()
{
	return servicesManager->render->GetCamera().x + servicesManager->render->GetCamera().w;
}

void SceneMatch::CheckPlayerLimits()
{
	float minXPos = servicesManager->render->GetCamera().x;
	float maxXPos = servicesManager->render->GetCamera().x + servicesManager->render->GetCamera().w;
	float limit;

	//Player1
	limit = minXPos + player1->margin;
	if (player1->position.x < limit)
	{
		player1->position.x = limit;
	}

	limit = maxXPos - player1->margin;
	if (player1->position.x > limit)
	{
		player1->position.x = limit;
	}

	//Player2
	limit = minXPos + player2->margin;
	if (player2->position.x < limit)
	{
		player2->position.x = limit;
	}

	limit = maxXPos - player2->margin;
	if (player2->position.x > limit)
	{
		player2->position.x = limit;
	}
}

void SceneMatch::SetCamXPosition()
{
	const fRect& camera = servicesManager->render->GetCamera();
	float minThreshold;
	float maxThreshold;

	float xMin, xMax;
	if (player1->position.x < player2->position.x)
	{
		xMin = player1->position.x;
		xMax = player2->position.x;
	}
	else
	{
		xMin = player2->position.x;
		xMax = player1->position.x;
	}
		

	//Move cam left?
	minThreshold = camera.x + scene25Percent;
	if (xMin < minThreshold &&	camera.x > stage->camMin.x)
	{
		camPosition.x = xMin - scene25Percent;
		maxThreshold = camPosition.x + scene75Percent;
		if ( xMax > maxThreshold )
		{
			camPosition.x = ((xMin + xMax) / 2) - scene50Percent;
		}
	}

	//Move cam right?
	maxThreshold = camera.x + scene75Percent;
	if (xMax > maxThreshold &&	camera.x < stage->camMax.x)
	{
		camPosition.x = xMax - scene75Percent;
		minThreshold = camPosition.x + scene25Percent;
		if (xMin < minThreshold)
		{
			camPosition.x = ((xMin + xMax) / 2) - scene50Percent;
		}
	}

	//Final check
	if (camPosition.x < stage->camMin.x)
		camPosition.x = stage->camMin.x;
	else if (camPosition.x > stage->camMax.x)
		camPosition.x = stage->camMax.x;
}

void SceneMatch::SetCamYPosition()
{
	if (player1->position.y == stage->groundLevel &&
		player2->position.y == stage->groundLevel)
	{
		camPosition.y = stage->camStart.y;
	}
	else
	{
		float yMin;
		if (player1->position.y < player2->position.y)
			yMin = player1->position.y;
		else
			yMin = player2->position.y;

		camPosition.y = stage->camStart.y - ((stage->groundLevel - yMin) * 0.08f); //8%
	}
}

void SceneMatch::SetCamPosition()
{
	servicesManager->render->SetCameraPostion(camPosition);
}
