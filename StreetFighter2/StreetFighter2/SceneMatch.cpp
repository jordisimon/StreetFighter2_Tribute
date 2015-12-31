#include "SceneMatch.h"
#include "Defines.h"
#include "Character.h"
#include "SceneMatchGUI.h"
#include "Stage.h"
#include "ServicesManager.h"
#include "ServiceCommandManager.h"
#include "ServiceRender.h"
#include "ServiceParticles.h"
#include "ServiceCollition.h"
#include "ServiceTime.h"
#include "CharacterFactory.h"
#include "StageFactory.h"
#include "MatchStateIntro.h"
#include "CommandContext.h"

SceneMatch::SceneMatch(const SceneMatchInfo& sceneInfo) : timer{ 1000, true }, paused{ false }, roundNumber{ 0 }
{
	GUI = new SceneMatchGUI();
	commandContextFight = servicesManager->commands->Load("Match_Command_Context");
	commandContextPause = servicesManager->commands->Load("Pause_Command_Context");
	
	stage = StageFactory::CreateStage(sceneInfo.stageType);
	player1 = CharacterFactory::CreateCharacter(sceneInfo.player1Type);
	player2 = CharacterFactory::CreateCharacter(sceneInfo.player2Type);
	timeLimit = sceneInfo.timeLimit;
}


SceneMatch::~SceneMatch()
{	
	RELEASE(player2);
	RELEASE(player1);
	RELEASE(stage);
	RELEASE(GUI);
}

bool SceneMatch::Init()
{
	bool ret;

	GUI->scene = this;
	
	commandContextFight->AddCommandListener(this);
	commandContextPause->AddCommandListener(this);

	ret = stage->Init();
	ret = ret && player1->Init();
	ret = ret && player2->Init();
	//Init GUI AFTER players (because it needs player id)
	GUI->Init();

	player1->groundLevel = stage->groundLevel;
	player2->groundLevel = stage->groundLevel;

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
	Scene::Start();

	GUI->Start();
	stage->Start();
	player1->Start();
	player2->Start();

	time = 99;
	camPosition = stage->camStart;
	SetCamPosition();
	player1->position = stage->p1StartPoint;
	player2->position = stage->p2StartPoint;
	player1->nextPosition = player1->position;
	player2->nextPosition = player2->position;
	player1->direction = Direction::RIGHT;
	player2->direction = Direction::LEFT;

	currentState = new MatchStateIntro(this);
	currentState->OnEnter();
	
	return true;
}

bool SceneMatch::Stop()
{
	player2->Stop();
	player1->Stop();
	stage->Stop();
	GUI->Stop();
	RELEASE(currentState);

	Scene::Stop();

	return true;
}

void SceneMatch::SetNewState(MatchState * state)
{
	if (state != nullptr)
	{
		currentState->OnExit();
		RELEASE(currentState);
		currentState = state;
		currentState->OnEnter();
	}
}

bool SceneMatch::ProcessInput(CommandData* commandData)
{
	if(started)
		SetNewState(currentState->ProcessInput(commandData));

	return true;
}

Entity::Result SceneMatch::UpdateState()
{
	if(started)
		SetNewState(currentState->UpdateState());

	return Entity::Result::R_OK;
}

Entity::Result SceneMatch::Draw() const
{
	if (started)
	{
		stage->Draw();
		player2->DrawShadow(stage->groundLevel);
		player1->DrawShadow(stage->groundLevel);
		player2->Draw();
		player1->Draw(); //Player1 painted over player 2
		servicesManager->particles->DrawParticles();
		servicesManager->collitions->DrawColliders();
		GUI->Draw();
	}
	return Entity::Result::R_OK;
}

void SceneMatch::CorrectPosition(fPoint & position, float margin)
{
	float minXPos = servicesManager->render->GetCamera().x;
	float maxXPos = servicesManager->render->GetCamera().x + servicesManager->render->GetCamera().w;
	float limit;

	limit = minXPos + margin;
	if (position.x < limit)
	{
		position.x = limit;
	}

	limit = maxXPos - margin;
	if (position.x > limit)
	{
		position.x = limit;
	}
}

void SceneMatch::MovePlayers()
{
	//First check if next position is outside margins and correct it
	CorrectPosition(player1->nextPosition, player1->bMargin);
	CorrectPosition(player2->nextPosition, player2->bMargin);


	bool nextTouching = player1->nextPosition.DistanceXTo(player2->nextPosition) < (player1->fMargin + player2->fMargin);

	//If next position not touching don't need to do anything else
	if (nextTouching)
	{
		Character* downPlayer;
		//Find whose player is up and whose is down
		if (player1->position.y < player2->position.y)
		{
			downPlayer = player2;
		}
		else
		{
			downPlayer = player2;
		}

		bool nextSameLevel = player1->nextPosition.DistanceYTo(player2->nextPosition) < downPlayer->height;

		//If they are in enough Y distance don't need to do anything else
		if (nextSameLevel)
		{
			float sceneMinXPos = servicesManager->render->GetCamera().x;
			float sceneMaxXPos = servicesManager->render->GetCamera().x + servicesManager->render->GetCamera().w;
			float limit;
			float distanceToLimit;

			float deltaPLeftMoveLeft = 0.0f;
			float deltaPRightMoveRight = 0.0f;

			bool currentTouching = player1->position.DistanceXTo(player2->position) < (player1->fMargin + player2->fMargin + 0.5f);

			if (currentTouching)
			{
				player1->IfMovingForwardRecalculatePositionWithPressingSpeed();
				player2->IfMovingForwardRecalculatePositionWithPressingSpeed();
			}

			float delta = (player1->fMargin + player2->fMargin) - player1->position.DistanceXTo(player2->position);
			deltaPLeftMoveLeft = delta / 2;
			deltaPRightMoveRight = delta / 2;

			Character* leftPlayer;
			Character* rightPlayer;
			//Find whose player is left and whose is right
			if (player1->position.x < player2->position.x)
			{
				leftPlayer = player1;
				rightPlayer = player2;
			}
			else
			{
				leftPlayer = player2;
				rightPlayer = player1;
			}

			limit = sceneMinXPos + leftPlayer->bMargin;
			distanceToLimit = leftPlayer->nextPosition.x - limit;

			//If player should move more than it can, we move as much as it can and transfer the remaining to the other player
			if (deltaPLeftMoveLeft > distanceToLimit)
			{
				deltaPRightMoveRight += deltaPLeftMoveLeft - distanceToLimit;
				deltaPLeftMoveLeft = distanceToLimit;
			}

			limit = sceneMaxXPos - rightPlayer->bMargin;
			distanceToLimit = limit - rightPlayer->nextPosition.x;

			if (deltaPRightMoveRight > distanceToLimit)
			{
				deltaPLeftMoveLeft += deltaPRightMoveRight - distanceToLimit;
				deltaPRightMoveRight = distanceToLimit;
			}

			leftPlayer->nextPosition.x -= deltaPLeftMoveLeft;
			rightPlayer->nextPosition.x += deltaPRightMoveRight;
		}
	}

	//Finally we set current position
	player1->position = player1->nextPosition;
	player2->position = player2->nextPosition;

	//Final check (just to be sure)
	CorrectPosition(player1->nextPosition, player1->bMargin);
	CorrectPosition(player2->nextPosition, player2->bMargin);
}

void SceneMatch::ApplyForceToPlayers(Character* forcedPlayer, Character* otherPlayer)
{
	if (forcedPlayer->hitBackwardMovement > 0.0f)
	{
		float movement;
		if (forcedPlayer->hitBackwardMovement > 1.0f)
		{
			movement = forcedPlayer->hitBackwardSpeed * servicesManager->time->frameTimeSeconds;
			forcedPlayer->hitBackwardMovement -= movement;
		}
		else
		{
			movement = forcedPlayer->hitBackwardMovement;
			forcedPlayer->hitBackwardMovement = 0.0f;
		}
		
		float sceneMaxXPos = servicesManager->render->GetCamera().x + servicesManager->render->GetCamera().w;
		float sceneMinXPos = servicesManager->render->GetCamera().x;
		float limit;
		float distanceToLimit;

		switch (forcedPlayer->direction)
		{
		case Direction::LEFT:
			limit = sceneMaxXPos - forcedPlayer->bMargin;
			distanceToLimit = limit - forcedPlayer->position.x;

			if (movement > distanceToLimit)
			{
				if (forcedPlayer->applyToOtherPlayer)
					otherPlayer->nextPosition.x = otherPlayer->position.x -(movement - distanceToLimit);
				movement = distanceToLimit;
			}

			forcedPlayer->nextPosition.x = forcedPlayer->position.x + movement;
			break;
		case Direction::RIGHT:
			limit = sceneMinXPos + forcedPlayer->bMargin;
			distanceToLimit = forcedPlayer->position.x - limit;

			if (movement > distanceToLimit)
			{
				if (forcedPlayer->applyToOtherPlayer)
					otherPlayer->nextPosition.x = otherPlayer->position.x + (movement - distanceToLimit);
				movement = distanceToLimit;
			}

			forcedPlayer->nextPosition.x = forcedPlayer->position.x - movement;
			break;
		}

		forcedPlayer->position = forcedPlayer->nextPosition;
		if (forcedPlayer->applyToOtherPlayer)
			otherPlayer->position = otherPlayer->nextPosition;

	}
}

void SceneMatch::CheckPlayerDirection()
{
	if (player1->position.x < player2->position.x)
	{
		player1->direction = Direction::RIGHT;
		player2->direction = Direction::LEFT;
	}
	else
	{
		player1->direction = Direction::LEFT;
		player2->direction = Direction::RIGHT;
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
		if (xMax > maxThreshold)
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

void SceneMatch::SetCamPosition() const
{
	servicesManager->render->SetCameraPostion(camPosition);
}


