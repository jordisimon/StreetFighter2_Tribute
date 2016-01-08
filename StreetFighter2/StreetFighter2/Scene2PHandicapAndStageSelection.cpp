#include "Scene2PHandicapAndStageSelection.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceRender.h"
#include "ServiceAudio.h"
#include "ServiceCommandManager.h"
#include "CommandContext.h"
#include "CommandData.h"
#include "CommandAction.h"
#include "SceneMatch.h"

#define MAX_HANDICAP 7
#define MAX_STAGES 12

Scene2PHandicapAndStageSelection::Scene2PHandicapAndStageSelection(const SceneMatchInfo& info)
	: validStages({false, true, false, false, true, false, false, false, false, false, false, false}),
	fadeColor{Color::Predefined::BLACK}
{
	configSection = "Scene_2P_Selection";

	matchInfo = info;

	bgColor.blue = 111;
	fadeColor.alpha = 128;

	commandContextMenu = servicesManager->commands->Load("Menu_Command_Context");
	servicesManager->commands->SetCurrentContext(commandContextMenu);
}


Scene2PHandicapAndStageSelection::~Scene2PHandicapAndStageSelection()
{
}

bool Scene2PHandicapAndStageSelection::Init()
{
	const fPoint& screenCenter = servicesManager->render->GetScreenCenter();
	const fRect& camera = servicesManager->render->GetCamera();

	texture = servicesManager->textures->Load(configSection);

	commandContextMenu->AddCommandListener(this);

	config->LoadSprite(handicapStageSelection, configSection, "handicapStageSelection");
	handicapStageSelectionPos.x = screenCenter.x;
	handicapStageSelectionPos.y = screenCenter.y;

	config->LoadSprite(forbbiden, configSection, "forbbiden2");

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

	config->LoadSprite(RyuName, configSection, "RyuName2");
	names.push_back(&RyuName);
	config->LoadSprite(HondaName, configSection, "HondaName2");
	names.push_back(&HondaName);
	config->LoadSprite(BlankaName, configSection, "BlankaName2");
	names.push_back(&BlankaName);
	config->LoadSprite(GuileName, configSection, "GuileName2");
	names.push_back(&GuileName);
	config->LoadSprite(KenName, configSection, "KenName2");
	names.push_back(&KenName);
	config->LoadSprite(ChunliName, configSection, "ChunliName2");
	names.push_back(&ChunliName);
	config->LoadSprite(ZanguiefName, configSection, "ZanguiefName2");
	names.push_back(&ZanguiefName);
	config->LoadSprite(DalshimName, configSection, "DalshimName2");
	names.push_back(&DalshimName);

	p1PortraitPos.x = screenCenter.x - 84;
	p1PortraitPos.y = screenCenter.y + 44;
	p1NamePos.x = screenCenter.x - 81;
	p1NamePos.y = screenCenter.y - 67;

	p2PortraitPos.x = screenCenter.x + 84;
	p2PortraitPos.y = screenCenter.y + 44;
	p2NamePos.x = screenCenter.x + 47;
	p2NamePos.y = screenCenter.y - 67;

	config->LoadSprite(handicap, configSection, "handicap");
	handicapPos.x = screenCenter.x - 1;
	handicapPos.y = screenCenter.y - 84;

	config->LoadSprite(stageSelect, configSection, "stageSelect");
	stageSelectPos.x = screenCenter.x - 1;
	stageSelectPos.y = screenCenter.y - 20;

	config->LoadSprite(red0, configSection, "red0");
	numbers.push_back(&red0);
	config->LoadSprite(red1, configSection, "red1");
	numbers.push_back(&red1);
	config->LoadSprite(red2, configSection, "red2");
	numbers.push_back(&red2);
	config->LoadSprite(red3, configSection, "red3");
	numbers.push_back(&red3);
	config->LoadSprite(red4, configSection, "red4");
	numbers.push_back(&red4);
	config->LoadSprite(red5, configSection, "red5");
	numbers.push_back(&red5);
	config->LoadSprite(red6, configSection, "red6");
	numbers.push_back(&red6);
	config->LoadSprite(red7, configSection, "red7");
	numbers.push_back(&red7);

	handicapFirstPosP1.x = screenCenter.x - 97;
	handicapFirstPosP1.y = screenCenter.y - 44;
	handicapFirstPosP2.x = screenCenter.x + 31;
	handicapFirstPosP2.y = screenCenter.y - 44;

	config->LoadSprite(japanFlag, configSection, "japanFlag");
	flags.push_back(&japanFlag);
	flags.push_back(&japanFlag);
	config->LoadSprite(brazilFlag, configSection, "brazilFlag");
	flags.push_back(&brazilFlag);
	config->LoadSprite(USAFlag, configSection, "USAFlag");
	flags.push_back(&USAFlag);
	flags.push_back(&USAFlag);
	config->LoadSprite(chinaFlag, configSection, "chinaFlag");
	flags.push_back(&chinaFlag);
	config->LoadSprite(USSRFlag, configSection, "USSRFlag");
	flags.push_back(&USSRFlag);
	config->LoadSprite(indiaFlag, configSection, "indiaFlag");
	flags.push_back(&indiaFlag);
	config->LoadSprite(thailandFlag, configSection, "thailandFlag");
	flags.push_back(&thailandFlag);
	flags.push_back(&thailandFlag);
	flags.push_back(&USAFlag);
	config->LoadSprite(spainFlag, configSection, "spainFlag");
	flags.push_back(&spainFlag);

	flagFirstPos.x = screenCenter.x - 91;
	flagFirstPos.y = screenCenter.y + 22;

	config->LoadSprite(RyuStageName, configSection, "RyuStageName");
	stageNames.push_back(&RyuStageName);
	config->LoadSprite(HondaStageName, configSection, "HondaStageName");
	stageNames.push_back(&HondaStageName);
	config->LoadSprite(BlankaStageName, configSection, "BlankaStageName");
	stageNames.push_back(&BlankaStageName);
	config->LoadSprite(GuileStageName, configSection, "GuileStageName");
	stageNames.push_back(&GuileStageName);
	config->LoadSprite(KenStageName, configSection, "KenStageName");
	stageNames.push_back(&KenStageName);
	config->LoadSprite(ChunliStageName, configSection, "ChunliStageName");
	stageNames.push_back(&ChunliStageName);
	config->LoadSprite(ZanguiefStageName, configSection, "ZanguiefStageName");
	stageNames.push_back(&ZanguiefStageName);
	config->LoadSprite(DalshimStageName, configSection, "DalshimStageName");
	stageNames.push_back(&DalshimStageName);
	config->LoadSprite(BisonStageName, configSection, "BisonStageName");
	stageNames.push_back(&BisonStageName);
	config->LoadSprite(SagatStageName, configSection, "SagatStageName");
	stageNames.push_back(&SagatStageName);
	config->LoadSprite(BalrogStageName, configSection, "BalrogStageName");
	stageNames.push_back(&BalrogStageName);
	config->LoadSprite(VegaStageName, configSection, "VegaStageName");
	stageNames.push_back(&VegaStageName);

	stageNamePos.x = screenCenter.x - 49;
	stageNamePos.y = screenCenter.y - 3;

	return true;
}

bool Scene2PHandicapAndStageSelection::CleanUp()
{
	commandContextMenu->RemoveCommandListener(this);
	return true;
}

bool Scene2PHandicapAndStageSelection::Start()
{
	Scene::Start();

	
	currentState = StageSelectionState::HANDICAP;
	p1Handicap = matchInfo.player1Handicap;
	p2Handicap = matchInfo.player2Handicap;
	stageSelection = (int)matchInfo.stageType;
	return true;
}

bool Scene2PHandicapAndStageSelection::ProcessInput(CommandData * commandData)
{
	if (!changing)
	{
		for (const auto& command : commandData->p1Actions)
		{
			switch (command)
			{
			case CommandAction::PAUSE:
				FillStageInfoAndSceneChange();
				break;

			case CommandAction::MOVE_UP:
				if (currentState == StageSelectionState::STAGE)
					currentState = StageSelectionState::HANDICAP;
				break;

			case CommandAction::MOVE_DOWN:
				if (currentState == StageSelectionState::HANDICAP)
					currentState = StageSelectionState::STAGE;
				break;

			case CommandAction::MOVE_LEFT:
				if (currentState == StageSelectionState::HANDICAP)
				{
					if (p1Handicap > 0)
						--p1Handicap;
				}
				else
				{
					--stageSelection;
					if (stageSelection < 0)
						stageSelection = MAX_STAGES - 1;
				}

				break;

			case CommandAction::MOVE_RIGHT:
				if (currentState == StageSelectionState::HANDICAP)
				{
					if (p1Handicap < MAX_HANDICAP)
						++p1Handicap;
				}
				else
				{
					++stageSelection;
					if (stageSelection >= MAX_STAGES)
						stageSelection = 0;
				}
				break;
			}
		}

		if (currentState == StageSelectionState::HANDICAP)
		{
			for (const auto& command : commandData->p2Actions)
			{
				switch (command)
				{
				case CommandAction::MOVE_LEFT:
					if (p2Handicap > 0)
						--p2Handicap;
					break;

				case CommandAction::MOVE_RIGHT:
					if (p2Handicap < MAX_HANDICAP)
						++p2Handicap;
					break;
				}
			}
		}
	}
	return true;
}

void Scene2PHandicapAndStageSelection::FillStageInfoAndSceneChange()
{
	if (validStages[stageSelection] && !changing)
	{
		servicesManager->audio->StopMusic(1.0f);
		matchInfo.player1Handicap = p1Handicap;
		matchInfo.player2Handicap = p2Handicap;
		matchInfo.stageType = (StageType)stageSelection;

		HandleSceneChange(new SceneMatch(matchInfo));
	}
}

Entity::Result Scene2PHandicapAndStageSelection::UpdateState()
{
	return Entity::Result::R_OK;
}

void Scene2PHandicapAndStageSelection::DrawHandicap(int handicap, const fPoint & initialPos) const
{
	fPoint finalPos = initialPos;
	finalPos.x += (handicap * 8);

	servicesManager->render->BlitGUI(texture, numbers[handicap]->GetRectPosition(finalPos), numbers[handicap]->rect);
}

void Scene2PHandicapAndStageSelection::DrawFlag() const
{
	fPoint position = flagFirstPos;

	if (stageSelection < 6)
		position.x += (32 * stageSelection);
	else
	{
		position.x += (32 * (stageSelection - 6));
		position.y += 40;
	}

	servicesManager->render->BlitGUI(texture, flags[stageSelection]->GetRectPosition(position), flags[stageSelection]->rect);


	if (!validStages[stageSelection])
		servicesManager->render->BlitGUI(texture, forbbiden.GetRectPosition(position), forbbiden.rect);
}

Entity::Result Scene2PHandicapAndStageSelection::Draw() const
{
	//Fill background blue
	servicesManager->render->SetDrawColor(bgColor);
	servicesManager->render->FillScreen();

	//Draw background pictures
	int character = (int)matchInfo.player1Type;
	servicesManager->render->BlitGUI(texture, portraits[character]->GetRectPosition(p1PortraitPos), portraits[character]->rect);
	character = (int)matchInfo.player2Type;
	servicesManager->render->BlitGUI(texture, portraits[character]->GetRectPosition(p2PortraitPos, Direction::LEFT), portraits[character]->rect, Direction::LEFT);

	//Draw opaque cape
	if (!changing)
	{
		servicesManager->render->SetDrawColor(fadeColor);
		servicesManager->render->FillScreen();
	}

	//Draw base sprite
	servicesManager->render->BlitGUI(texture, handicapStageSelection.GetRectPosition(handicapStageSelectionPos), handicapStageSelection.rect);

	//Draw names
	character = (int)matchInfo.player1Type;
	servicesManager->render->BlitGUI(texture, names[character]->GetRectPosition(p1NamePos), names[character]->rect);
	character = (int)matchInfo.player2Type;
	servicesManager->render->BlitGUI(texture, names[character]->GetRectPosition(p2NamePos), names[character]->rect);

	switch (currentState)
	{
	case StageSelectionState::HANDICAP:
		servicesManager->render->BlitGUI(texture, handicap.GetRectPosition(handicapPos), handicap.rect);
		break;
	case StageSelectionState::STAGE:
		servicesManager->render->BlitGUI(texture, stageSelect.GetRectPosition(stageSelectPos), stageSelect.rect);
		break;
	default:
		break;
	}

	DrawHandicap(p1Handicap, handicapFirstPosP1);
	DrawHandicap(p2Handicap, handicapFirstPosP2);

	DrawFlag();

	servicesManager->render->BlitGUI(texture, stageNames[stageSelection]->GetRectPosition(stageNamePos), stageNames[stageSelection]->rect);

	return Entity::Result::R_OK;
}
