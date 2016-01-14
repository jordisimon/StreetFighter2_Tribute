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
#include "Scene2PMatchResult.h"
#include "Collider.h"
#include "ColliderType.h"
#include "CharacterFactory.h"
#include "StageFactory.h"
#include "MatchStateIntro.h"
#include "CommandContext.h"
#include "Particle.h"

SceneMatch::SceneMatch(const SceneMatchInfo& sceneInfo) : timer { 1000, true }, paused{ false }, roundNumber{ 0 }
{
	matchInfo = sceneInfo;
	GUI = new SceneMatchGUI();
	commandContextFight = servicesManager->commands->Load("Match_Command_Context");
	commandContextPause = servicesManager->commands->Load("Pause_Command_Context");
	
	stage = StageFactory::CreateStage(matchInfo.stageType);
	player1 = CharacterFactory::CreateCharacter(matchInfo.player1Type);
	player1->handicap = matchInfo.player1Handicap;
	player2 = CharacterFactory::CreateCharacter(matchInfo.player2Type);
	player2->handicap = matchInfo.player2Handicap;
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

	const fRect& camera = servicesManager->render->GetCamera();

	timeLimit = config->LoadBoolValue("Options", "timeLimit", "1");

	fRect colliderRect{ 0,0,2,camera.h };
	colliderRect.x = camera.x - 10;
	boxLeftCollider = servicesManager->collitions->CreateCollider(ColliderType::SCENE_BOX, colliderRect, nullptr, Color::Predefined::WHITE);
	colliderRect.x = camera.x + camera.w + 8;
	boxRightCollider = servicesManager->collitions->CreateCollider(ColliderType::SCENE_BOX, colliderRect, nullptr, Color::Predefined::WHITE);
	
	commandContextFight->AddCommandListener(this);
	commandContextPause->AddCommandListener(this);

	ret = stage->Init();
	ret = ret && player1->Init();
	ret = ret && player2->Init();
	player1->rival = player2;
	player2->rival = player1;

	//Init GUI AFTER players (because it needs player id)
	GUI->Init();

	player1->groundLevel = stage->groundLevel;
	player2->groundLevel = stage->groundLevel;

	player1->playerNumber = 1;
	player2->playerNumber = 2;

	gravity = config->LoadFloatValue("Physics", "gravity", "-0.3f");
	player1->gravity = gravity;
	player2->gravity = gravity;

	scene25Percent = camera.w / 4;
	scene50Percent = camera.w / 2;
	scene75Percent = camera.w / 4 * 3;

	++matchInfo.battleNumber;

	return ret;
}

bool SceneMatch::CleanUp()
{
	commandContextFight->RemoveCommandListener(this);
	commandContextPause->RemoveCommandListener(this);

	boxLeftCollider->toDelete = true;
	boxRightCollider->toDelete = true;

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
	//servicesManager->render->SetCameraPostion(camPosition);

	SetCollidersPosition();

	player1->position = stage->p1StartPoint;
	player2->position = stage->p2StartPoint;
	player1->nextPosition = player1->position;
	player2->nextPosition = player2->position;
	player1->SetDirection(Direction::RIGHT);
	player2->SetDirection(Direction::LEFT);

	currentState = new MatchStateIntro(this);
	currentState->OnEnter();

	vitalScore = 0;
	timeScore = 0;
	
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

void SceneMatch::SceneChange()
{
	if (matchInfo.twoPlayers && !changing)
	{
		//Scene manager load scene match result
		HandleSceneChange(new Scene2PMatchResult(matchInfo));
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

		//If player1 beign grabbed, then painted background, else always foreground
		if (player1->isGrabbed)
		{
			player1->Draw();
			player2->Draw();
		}
		else
		{
			player2->Draw();
			player1->Draw(); 
		}
		servicesManager->particles->DrawParticles();
		stage->DrawForeground();
		servicesManager->collitions->DrawColliders();
		GUI->Draw();
	}
	return Entity::Result::R_OK;
}

void SceneMatch::PauseAllTimers()
{
	if (timeLimit)
		timer.Pause();

	player1->PauseAllTimers();
	player2->PauseAllTimers();
}

void SceneMatch::ResumeAllTimers()
{
	if (timeLimit)
		timer.Resume();

	player1->ResumeAllTimers();
	player2->ResumeAllTimers();
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

	//Special case if any player is being grabbed
	if (player1->isGrabbed || player2->isGrabbed)
		nextTouching = false;

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
	CorrectPosition(player1->position, player1->bMargin);
	CorrectPosition(player2->position, player2->bMargin);
}

void SceneMatch::ApplyForceToPlayers(Character* forcedPlayer, Character* otherPlayer)
{
	if (forcedPlayer->hitBackwardMovement > 0.0f)
	{
		float movement;
		if (forcedPlayer->hitBackwardMovement > 1.0f)
		{
			movement = (forcedPlayer->hitBackwardSpeed * servicesManager->time->frameTimeSeconds) * forcedPlayer->updateOverallSpeed;

			if(movement < forcedPlayer->hitBackwardMovement)
				forcedPlayer->hitBackwardMovement -= movement;
			else
			{
				movement = forcedPlayer->hitBackwardMovement;
				forcedPlayer->hitBackwardMovement = 0.0f;
			}
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
				//Only apply to other player if he is close enough
				if (forcedPlayer->applyBackwardMovementToOtherPlayerRatio > 0.0f && otherPlayer->position.x > sceneMaxXPos - (scene25Percent * 1.5f))
					otherPlayer->nextPosition.x = otherPlayer->position.x - ((movement - distanceToLimit) * forcedPlayer->applyBackwardMovementToOtherPlayerRatio);
				movement = distanceToLimit;
			}

			forcedPlayer->nextPosition.x = forcedPlayer->position.x + movement;
			break;
		case Direction::RIGHT:
			limit = sceneMinXPos + forcedPlayer->bMargin;
			distanceToLimit = forcedPlayer->position.x - limit;

			if (movement > distanceToLimit)
			{
				//Only apply to other player if he is close enough
				if (forcedPlayer->applyBackwardMovementToOtherPlayerRatio > 0.0f && otherPlayer->position.x < sceneMinXPos + (scene25Percent * 1.5f))
					otherPlayer->nextPosition.x = otherPlayer->position.x + ((movement - distanceToLimit) * forcedPlayer->applyBackwardMovementToOtherPlayerRatio);
				movement = distanceToLimit;
			}

			forcedPlayer->nextPosition.x = forcedPlayer->position.x - movement;
			break;
		}

		forcedPlayer->position = forcedPlayer->nextPosition;
		if (forcedPlayer->applyBackwardMovementToOtherPlayerRatio > 0.0f)
			otherPlayer->position = otherPlayer->nextPosition;

	}
}

void SceneMatch::UpdatePlayersCollidersPosition()
{
	player1->UpdateColliders();
	player2->UpdateColliders();
}

void SceneMatch::CheckPlayerDirection()
{
	if (player1->position.x < player2->position.x)
	{
		player1->SetDirection(Direction::RIGHT);
		player2->SetDirection(Direction::LEFT);
	}
	else
	{
		player1->SetDirection(Direction::LEFT);
		player2->SetDirection(Direction::RIGHT);
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

void SceneMatch::SetCollidersPosition()
{
	fPoint boxPosition;
	boxPosition.y = camPosition.y;
	boxPosition.x = camPosition.x - 10;
	boxLeftCollider->SetPosition(boxPosition);
	boxPosition.x = camPosition.x + servicesManager->render->GetCamera().w + 8;
	boxRightCollider->SetPosition(boxPosition);
}


