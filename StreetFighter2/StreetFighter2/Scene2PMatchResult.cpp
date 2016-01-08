#include "Scene2PMatchResult.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceRender.h"
#include "ServiceAudio.h"
#include "ServiceCommandManager.h"
#include "CommandContext.h"
#include "CommandData.h"
#include "Scene2PCharacterSelection.h"
#include "SF2Stats.h"

int Scene2PMatchResult::matchResultSfx = -1;

Scene2PMatchResult::Scene2PMatchResult(const SceneMatchInfo& info): fadeColor{ Color::Predefined::BLACK }
{
	configSection = "Scene_2P_Selection";

	matchInfo = info;
	fadeColor.alpha = 128;

	commandContextMenu = servicesManager->commands->Load("Menu_Command_Context");
	servicesManager->commands->SetCurrentContext(commandContextMenu);

	if (matchResultSfx == -1) matchResultSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Music\\MatchResult.ogg");
}


Scene2PMatchResult::~Scene2PMatchResult()
{
}

bool Scene2PMatchResult::Init()
{
	const fPoint& screenCenter = servicesManager->render->GetScreenCenter();

	texture = servicesManager->textures->Load(configSection);

	commandContextMenu->AddCommandListener(this);

	config->LoadSprite(playerStats, configSection, "playerStats");
	playerStatsPos.x = screenCenter.x;
	playerStatsPos.y = screenCenter.y - 95;

	config->LoadSprite(RyuBigPortrait, configSection, "RyuBigPortrait");
	portraits.push_back(&RyuBigPortrait);
	config->LoadSprite(HondaBigPortrait, configSection, "HondaBigPortrait");
	portraits.push_back(&HondaBigPortrait);
	config->LoadSprite(BlankaBigPortrait, configSection, "BlankaBigPortrait");
	portraits.push_back(&BlankaBigPortrait);
	config->LoadSprite(GuileBigPortrait, configSection, "GuileBigPortrait");
	portraits.push_back(&GuileBigPortrait);
	config->LoadSprite(KenBigPortrait, configSection, "KenBigPortrait");
	portraits.push_back(&KenBigPortrait);
	config->LoadSprite(ChunliBigPortrait, configSection, "ChunliBigPortrait");
	portraits.push_back(&ChunliBigPortrait);
	config->LoadSprite(ZanguiefBigPortrait, configSection, "ZanguiefBigPortrait");
	portraits.push_back(&ZanguiefBigPortrait);
	config->LoadSprite(DalshimBigPortrait, configSection, "DalshimBigPortrait");
	portraits.push_back(&DalshimBigPortrait);

	p1PortraitPos.x = screenCenter.x - 84;
	p1PortraitPos.y = screenCenter.y + 44;

	p2PortraitPos.x = screenCenter.x + 84;
	p2PortraitPos.y = screenCenter.y + 44;

	config->LoadSprite(whiteBig0, configSection, "whiteBig0");
	whiteBigNumbers.push_back(&whiteBig0);
	config->LoadSprite(whiteBig1, configSection, "whiteBig1");
	whiteBigNumbers.push_back(&whiteBig1);
	config->LoadSprite(whiteBig2, configSection, "whiteBig2");
	whiteBigNumbers.push_back(&whiteBig2);
	config->LoadSprite(whiteBig3, configSection, "whiteBig3");
	whiteBigNumbers.push_back(&whiteBig3);
	config->LoadSprite(whiteBig4, configSection, "whiteBig4");
	whiteBigNumbers.push_back(&whiteBig4);
	config->LoadSprite(whiteBig5, configSection, "whiteBig5");
	whiteBigNumbers.push_back(&whiteBig5);
	config->LoadSprite(whiteBig6, configSection, "whiteBig6");
	whiteBigNumbers.push_back(&whiteBig6);
	config->LoadSprite(whiteBig7, configSection, "whiteBig7");
	whiteBigNumbers.push_back(&whiteBig7);
	config->LoadSprite(whiteBig8, configSection, "whiteBig8");
	whiteBigNumbers.push_back(&whiteBig8);
	config->LoadSprite(whiteBig9, configSection, "whiteBig9");
	whiteBigNumbers.push_back(&whiteBig9);

	config->LoadSprite(redBig0, configSection, "redBig0");
	redBigNumbers.push_back(&redBig0);
	config->LoadSprite(redBig1, configSection, "redBig1");
	redBigNumbers.push_back(&redBig1);
	config->LoadSprite(redBig2, configSection, "redBig2");
	redBigNumbers.push_back(&redBig2);
	config->LoadSprite(redBig3, configSection, "redBig3");
	redBigNumbers.push_back(&redBig3);
	config->LoadSprite(redBig4, configSection, "redBig4");
	redBigNumbers.push_back(&redBig4);
	config->LoadSprite(redBig5, configSection, "redBig5");
	redBigNumbers.push_back(&redBig5);
	config->LoadSprite(redBig6, configSection, "redBig6");
	redBigNumbers.push_back(&redBig6);
	config->LoadSprite(redBig7, configSection, "redBig7");
	redBigNumbers.push_back(&redBig7);
	config->LoadSprite(redBig8, configSection, "redBig8");
	redBigNumbers.push_back(&redBig8);
	config->LoadSprite(redBig9, configSection, "redBig9");
	redBigNumbers.push_back(&redBig9);

	p1FirstNumberPos.x = screenCenter.x - 108;
	p1FirstNumberPos.y = screenCenter.y - 47;
	p2FirstNumberPos.x = screenCenter.x + 44;
	p2FirstNumberPos.y = screenCenter.y - 47;

	numberHDistance = 16;
	numberVDistance = 16;

	p1TotalFirstNumberPos.x = screenCenter.x - 108;
	p1TotalFirstNumberPos.y = screenCenter.y + 82;
	p2TotalFirstNumberPos.x = screenCenter.x + 44;
	p2TotalFirstNumberPos.y = screenCenter.y + 82;

	return true;
}

bool Scene2PMatchResult::CleanUp()
{
	commandContextMenu->RemoveCommandListener(this);
	return true;
}

bool Scene2PMatchResult::Start()
{
	Scene::Start();

	servicesManager->audio->PlayFx(matchResultSfx);
	return true;
}

bool Scene2PMatchResult::ProcessInput(CommandData * commandData)
{
	if (!changing)
	{
		for (const auto& command : commandData->p1Actions)
		{
			switch (command)
			{
			case CommandAction::PAUSE:
				HandleSceneChange(new Scene2PCharacterSelection(matchInfo));
				return true;
				break;
			}
		}

		for (const auto& command : commandData->p2Actions)
		{
			switch (command)
			{
			case CommandAction::PAUSE:
				HandleSceneChange(new Scene2PCharacterSelection(matchInfo));
				return true;
				break;
			}
		}
	}
	return true;
}

void Scene2PMatchResult::DrawCharacterStats(const fPoint& firstDigitPos, unsigned int wins, unsigned int draws, unsigned int loses) const
{
	int firstDigit, secondDigit;
	fPoint currentPos = firstDigitPos;
	const std::vector<Sprite*>* digitsVector;
	const Sprite* firstNumSprite;
	const Sprite* secondNumSprite;

	//Red or white digits?
	if (wins > loses)
		digitsVector = &redBigNumbers;
	else
		digitsVector = &whiteBigNumbers;

	//Wins
	firstDigit = (int)(wins / 10);
	if (firstDigit > 0)
	{
		firstNumSprite = (*digitsVector)[firstDigit];
		servicesManager->render->BlitGUI(texture, firstNumSprite->GetRectPosition(currentPos), firstNumSprite->rect);
	}
	currentPos.x += 8;
	secondDigit = wins % 10;
	secondNumSprite = (*digitsVector)[secondDigit];
	servicesManager->render->BlitGUI(texture, secondNumSprite->GetRectPosition(currentPos), secondNumSprite->rect);

	//Loses
	currentPos.x += numberHDistance;
	firstDigit = (int)(loses / 10);
	if (firstDigit > 0)
	{
		firstNumSprite = (*digitsVector)[firstDigit];
		servicesManager->render->BlitGUI(texture, firstNumSprite->GetRectPosition(currentPos), firstNumSprite->rect);
	}
	currentPos.x += 8;
	secondDigit = loses % 10;
	secondNumSprite = (*digitsVector)[secondDigit];
	servicesManager->render->BlitGUI(texture, secondNumSprite->GetRectPosition(currentPos), secondNumSprite->rect);

	//Draws
	currentPos.x += numberHDistance;
	firstDigit = (int)(draws / 10);
	if (firstDigit > 0)
	{
		firstNumSprite = (*digitsVector)[firstDigit];
		servicesManager->render->BlitGUI(texture, firstNumSprite->GetRectPosition(currentPos), firstNumSprite->rect);
	}
	currentPos.x += 8;
	secondDigit = draws % 10;
	secondNumSprite = (*digitsVector)[secondDigit];
	servicesManager->render->BlitGUI(texture, secondNumSprite->GetRectPosition(currentPos), secondNumSprite->rect);
}

void Scene2PMatchResult::DrawPlayerStats(const fPoint & firstDigitPos, const fPoint & totalsFirstDigitPos, const PlayerStats & playerStats) const
{
	fPoint currentPos = firstDigitPos;

	//Characters
	DrawCharacterStats(currentPos, playerStats.Ryu.wins, playerStats.Ryu.draws, playerStats.Ryu.loses);
	currentPos.y += numberVDistance;
	DrawCharacterStats(currentPos, playerStats.Honda.wins, playerStats.Honda.draws, playerStats.Honda.loses);
	currentPos.y += numberVDistance;
	DrawCharacterStats(currentPos, playerStats.Blanka.wins, playerStats.Blanka.draws, playerStats.Blanka.loses);
	currentPos.y += numberVDistance;
	DrawCharacterStats(currentPos, playerStats.Guile.wins, playerStats.Guile.draws, playerStats.Guile.loses);
	currentPos.y += numberVDistance;
	DrawCharacterStats(currentPos, playerStats.Ken.wins, playerStats.Ken.draws, playerStats.Ken.loses);
	currentPos.y += numberVDistance;
	DrawCharacterStats(currentPos, playerStats.Chunli.wins, playerStats.Chunli.draws, playerStats.Chunli.loses);
	currentPos.y += numberVDistance;
	DrawCharacterStats(currentPos, playerStats.Zanguief.wins, playerStats.Zanguief.draws, playerStats.Zanguief.loses);
	currentPos.y += numberVDistance;
	DrawCharacterStats(currentPos, playerStats.Dalshim.wins, playerStats.Dalshim.draws, playerStats.Dalshim.loses);

	//Totals
	DrawCharacterStats(totalsFirstDigitPos, playerStats.wins, playerStats.draws, playerStats.loses);

}


Entity::Result Scene2PMatchResult::Draw() const
{
	//Draw background pictures
	int character = (int)matchInfo.player1Type;
	servicesManager->render->BlitGUI(texture, portraits[character]->GetRectPosition(p1PortraitPos), portraits[character]->rect);
	character = (int)matchInfo.player2Type;
	servicesManager->render->BlitGUI(texture, portraits[character]->GetRectPosition(p2PortraitPos, Direction::LEFT), portraits[character]->rect, Direction::LEFT);

	servicesManager->render->SetDrawColor(fadeColor);
	servicesManager->render->FillScreen();

	//Draw base sprite
	servicesManager->render->BlitGUI(texture, playerStats.GetRectPosition(playerStatsPos), playerStats.rect);

	//Draw player stats
	DrawPlayerStats(p1FirstNumberPos, p1TotalFirstNumberPos, SF2Stats::p1Stats);
	DrawPlayerStats(p2FirstNumberPos, p2TotalFirstNumberPos, SF2Stats::p2Stats);

	return Entity::Result::R_OK;
}
