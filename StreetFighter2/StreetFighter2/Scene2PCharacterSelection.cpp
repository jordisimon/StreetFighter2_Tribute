#include "Scene2PCharacterSelection.h"
#include "Config.h"
#include "ServicesManager.h"
#include "ServiceTextures.h"
#include "ServiceRender.h"
#include "ServiceAudio.h"
#include "ServiceCommandManager.h"
#include "CommandContext.h"
#include "CommandData.h"
#include "CharacterType.h"
#include "Scene2PHandicapAndStageSelection.h"
#include "SF2Stats.h"

#define MAX_CHARACTERS 8

int Scene2PCharacterSelection::optionMoveSfx = -1;
int Scene2PCharacterSelection::characterConfirmSfx = -1;

using namespace std;

Scene2PCharacterSelection::Scene2PCharacterSelection(const SceneMatchInfo& info) : validCharacters({true, false, false, false, true, false, false, false})
{
	configSection = "Scene_2P_Selection";

	matchInfo = info;

	bgColor.blue = 111;

	commandContextMenu = servicesManager->commands->Load("Menu_Command_Context");
	servicesManager->commands->SetCurrentContext(commandContextMenu);

	if (optionMoveSfx == -1) optionMoveSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Menu\\OptionMove.ogg");
	if (characterConfirmSfx == -1) characterConfirmSfx = servicesManager->audio->LoadFx("Assets\\Sound\\Sfx\\Menu\\CharacterConfirm.ogg");
}


Scene2PCharacterSelection::~Scene2PCharacterSelection()
{
}

bool Scene2PCharacterSelection::Init()
{
	const fPoint& screenCenter = servicesManager->render->GetScreenCenter();
	const fRect& camera = servicesManager->render->GetCamera();

	texture = servicesManager->textures->Load(configSection);

	commandContextMenu->AddCommandListener(this);

	config->LoadSprite(playerSelection, configSection, "playerSelection");
	playerSelectionPos.x = screenCenter.x;
	playerSelectionPos.y = screenCenter.y - 90;

	config->LoadSprite(forbbiden, configSection, "forbbiden");

	config->LoadAnimation(p1Cursor, configSection, "p1Cursor");
	config->LoadAnimation(p2Cursor, configSection, "p2Cursor");
	playerFirstPos.x = screenCenter.x - 48;
	playerFirstPos.y = screenCenter.y - 70;

	config->LoadSprite(RyuPortrait, configSection, "RyuPortrait");
	portraits.push_back(&RyuPortrait);
	config->LoadSprite(HondaPortrait, configSection, "HondaPortrait");
	portraits.push_back(&HondaPortrait);
	config->LoadSprite(BlankaPortrait, configSection, "BlankaPortrait");
	portraits.push_back(&BlankaPortrait);
	config->LoadSprite(GuilePortrait, configSection, "GuilePortrait");
	portraits.push_back(&GuilePortrait);
	config->LoadSprite(KenPortrait, configSection, "KenPortrait");
	portraits.push_back(&KenPortrait);
	config->LoadSprite(ChunliPortrait, configSection, "ChunliPortrait");
	portraits.push_back(&ChunliPortrait);
	config->LoadSprite(ZanguiefPortrait, configSection, "ZanguiefPortrait");
	portraits.push_back(&ZanguiefPortrait);
	config->LoadSprite(DalshimPortrait, configSection, "DalshimPortrait");
	portraits.push_back(&DalshimPortrait);

	config->LoadSprite(RyuName, configSection, "RyuName");
	names.push_back(&RyuName);
	config->LoadSprite(HondaName, configSection, "HondaName");
	names.push_back(&HondaName);
	config->LoadSprite(BlankaName, configSection, "BlankaName");
	names.push_back(&BlankaName);
	config->LoadSprite(GuileName, configSection, "GuileName");
	names.push_back(&GuileName);
	config->LoadSprite(KenName, configSection, "KenName");
	names.push_back(&KenName);
	config->LoadSprite(ChunliName, configSection, "ChunliName");
	names.push_back(&ChunliName);
	config->LoadSprite(ZanguiefName, configSection, "ZanguiefName");
	names.push_back(&ZanguiefName);
	config->LoadSprite(DalshimName, configSection, "DalshimName");
	names.push_back(&DalshimName);

	p1PortraitPos.x = screenCenter.x - 92;
	p1PortraitPos.y = screenCenter.y + 7;
	p1NamePos.x = screenCenter.x - 92;
	p1NamePos.y = screenCenter.y + 8;

	p2PortraitPos.x = screenCenter.x + 92;
	p2PortraitPos.y = screenCenter.y + 7;
	p2NamePos.x = screenCenter.x + 92;
	p2NamePos.y = screenCenter.y + 8;

	config->LoadSprite(white0, configSection, "white0");
	numbers.push_back(&white0);
	config->LoadSprite(white1, configSection, "white1");
	numbers.push_back(&white1);
	config->LoadSprite(white2, configSection, "white2");
	numbers.push_back(&white2);
	config->LoadSprite(white3, configSection, "white3");
	numbers.push_back(&white3);
	config->LoadSprite(white4, configSection, "white4");
	numbers.push_back(&white4);
	config->LoadSprite(white5, configSection, "white5");
	numbers.push_back(&white5);
	config->LoadSprite(white6, configSection, "white6");
	numbers.push_back(&white6);
	config->LoadSprite(white7, configSection, "white7");
	numbers.push_back(&white7);
	config->LoadSprite(white8, configSection, "white8");
	numbers.push_back(&white8);
	config->LoadSprite(white9, configSection, "white9");
	numbers.push_back(&white9);

	c1FirstDigitPos.x = screenCenter.x - 104;
	c1FirstDigitPos.y = screenCenter.y + 21;
	p1FirstDigitPos.x = screenCenter.x - 104;
	p1FirstDigitPos.y = screenCenter.y + 70;

	c2FirstDigitPos.x = screenCenter.x + 24;
	c2FirstDigitPos.y = screenCenter.y + 21;
	p2FirstDigitPos.x = screenCenter.x + 24;
	p2FirstDigitPos.y = screenCenter.y + 70;

	numberHDistance = 32;
	numberVDistance = 16;

	return true;
}

bool Scene2PCharacterSelection::CleanUp()
{
	commandContextMenu->RemoveCommandListener(this);
	return true;
}

bool Scene2PCharacterSelection::Start()
{
	Scene::Start();

	p1Selected = false;
	p2Selected = false;
	p1Selection = (int)matchInfo.player1Type;
	p2Selection = (int)matchInfo.player2Type;
	servicesManager->audio->PlayMusic("Assets\\Sound\\Music\\CharacterSelect.ogg", 0.0f);
	return true;
}

bool Scene2PCharacterSelection::ProcessInput(CommandData * commandData)
{
	if (!changing)
	{
		int nextPos;

		if (!p1Selected)
		{
			for (const auto& command : commandData->p1Actions)
			{
				switch (command)
				{
				case CommandAction::PAUSE:
					if (validCharacters[p1Selection])
					{
						servicesManager->audio->PlayFx(characterConfirmSfx);
						p1Cursor.ResetAnimation();
						p1Selected = true;
						if (p1Selected && p2Selected)
							FillCharacterInfoAndSceneChange();
						return true;
					}
					break;

				case CommandAction::MOVE_UP:
					if (p1Selection >= 4 && p1Selection - 4 != p2Selection)
					{
						servicesManager->audio->PlayFx(optionMoveSfx);
						p1Selection -= 4;
					}
					break;
				case CommandAction::MOVE_DOWN:
					if (p1Selection < 4 && p1Selection + 4 != p2Selection)
					{
						servicesManager->audio->PlayFx(optionMoveSfx);
						p1Selection += 4;
					}
					break;

				case CommandAction::MOVE_LEFT:
					nextPos = p1Selection - 1;
					if (nextPos == p2Selection)
						nextPos -= 1;

					if ((p1Selection < 4 && nextPos >= 0) ||
						(p1Selection >= 4 && nextPos >= 4))
					{
						p1Selection = nextPos;
						servicesManager->audio->PlayFx(optionMoveSfx);
					}
					break;

				case CommandAction::MOVE_RIGHT:
					nextPos = p1Selection + 1;
					if (nextPos == p2Selection)
						nextPos += 1;

					if ((p1Selection < 4 && nextPos < 4) ||
						(p1Selection >= 4 && nextPos < MAX_CHARACTERS))
					{
						p1Selection = nextPos;
						servicesManager->audio->PlayFx(optionMoveSfx);
					}
					break;
				}
			}
		}

		if (!p2Selected)
		{

			for (const auto& command : commandData->p2Actions)
			{
				switch (command)
				{
				case CommandAction::PAUSE:
					if (validCharacters[p2Selection])
					{
						servicesManager->audio->PlayFx(characterConfirmSfx);
						p2Cursor.ResetAnimation();
						p2Selected = true;
						if (p1Selected && p2Selected)
							FillCharacterInfoAndSceneChange();
						return true;
					}
					break;

				case CommandAction::MOVE_UP:
					if (p2Selection >= 4 && p2Selection - 4 != p1Selection)
					{
						servicesManager->audio->PlayFx(optionMoveSfx);
						p2Selection -= 4;
					}
					break;
				case CommandAction::MOVE_DOWN:
					if (p2Selection < 4 && p2Selection + 4 != p1Selection)
					{
						servicesManager->audio->PlayFx(optionMoveSfx);
						p2Selection += 4;
					}
					break;

				case CommandAction::MOVE_LEFT:
					nextPos = p2Selection - 1;
					if (nextPos == p1Selection)
						nextPos -= 1;

					if ((p2Selection < 4 && nextPos >= 0) ||
						(p2Selection >= 4 && nextPos >= 4))
					{
						p2Selection = nextPos;
						servicesManager->audio->PlayFx(optionMoveSfx);
					}
					break;

				case CommandAction::MOVE_RIGHT:
					nextPos = p2Selection + 1;
					if (nextPos == p1Selection)
						nextPos += 1;

					if ((p2Selection < 4 && nextPos < 4) ||
						(p2Selection >= 4 && nextPos < MAX_CHARACTERS))
					{
						p2Selection = nextPos;
						servicesManager->audio->PlayFx(optionMoveSfx);
					}
					break;
				}
			}
		}
	}
	return true;
}

void Scene2PCharacterSelection::FillCharacterInfoAndSceneChange()
{
	if (!changing)
	{
		matchInfo.player1Type = (CharacterType)p1Selection;
		matchInfo.player2Type = (CharacterType)p2Selection;
		HandleSceneChange(new Scene2PHandicapAndStageSelection(matchInfo));
	}
}

Entity::Result Scene2PCharacterSelection::UpdateState()
{
	if(!p1Selected)
		p1Cursor.UpdateCurrentFrame();

	if(!p2Selected)
		p2Cursor.UpdateCurrentFrame();

	return Entity::Result::R_OK;
}

Entity::Result Scene2PCharacterSelection::Draw() const
{
	//Fill background blue
	servicesManager->render->SetDrawColor(bgColor);
	servicesManager->render->FillScreen();

	//Draw base sprite
	servicesManager->render->BlitGUI(texture, playerSelection.GetRectPosition(playerSelectionPos), playerSelection.rect);

	//P1Selection
	servicesManager->render->BlitGUI(texture, portraits[p1Selection]->GetRectPosition(p1PortraitPos), portraits[p1Selection]->rect);
	servicesManager->render->BlitGUI(texture, names[p1Selection]->GetRectPosition(p1NamePos), names[p1Selection]->rect);

	//P2Selection
	servicesManager->render->BlitGUI(texture, portraits[p2Selection]->GetRectPosition(p2PortraitPos, Direction::LEFT), portraits[p2Selection]->rect, Direction::LEFT);
	servicesManager->render->BlitGUI(texture, names[p2Selection]->GetRectPosition(p2NamePos), names[p2Selection]->rect);

	//Draw stats
	DrawAllStats();

	//Cursors
	if (p1Selection > p2Selection)
	{
		DrawCursor(p2Selection, p2Cursor);
		DrawCursor(p1Selection, p1Cursor);
	}
	else
	{
		DrawCursor(p1Selection, p1Cursor);
		DrawCursor(p2Selection, p2Cursor);
	}

	return Entity::Result::R_OK;
}

void Scene2PCharacterSelection::DrawAllStats() const
{
	switch (p1Selection)
	{
	case 0:
		DrawStats(c1FirstDigitPos, SF2Stats::p1Stats.Ryu.wins, SF2Stats::p1Stats.Ryu.draws, SF2Stats::p1Stats.Ryu.loses, SF2Stats::p1Stats.Ryu.SPKO);
		break;
	case 1:
		DrawStats(c1FirstDigitPos, SF2Stats::p1Stats.Honda.wins, SF2Stats::p1Stats.Honda.draws, SF2Stats::p1Stats.Honda.loses, SF2Stats::p1Stats.Honda.SPKO);
		break;
	case 2:
		DrawStats(c1FirstDigitPos, SF2Stats::p1Stats.Blanka.wins, SF2Stats::p1Stats.Blanka.draws, SF2Stats::p1Stats.Blanka.loses, SF2Stats::p1Stats.Blanka.SPKO);
		break;
	case 3:
		DrawStats(c1FirstDigitPos, SF2Stats::p1Stats.Guile.wins, SF2Stats::p1Stats.Guile.draws, SF2Stats::p1Stats.Guile.loses, SF2Stats::p1Stats.Guile.SPKO);
		break;
	case 4:
		DrawStats(c1FirstDigitPos, SF2Stats::p1Stats.Ken.wins, SF2Stats::p1Stats.Ken.draws, SF2Stats::p1Stats.Ken.loses, SF2Stats::p1Stats.Ken.SPKO);
		break;
	case 5:
		DrawStats(c1FirstDigitPos, SF2Stats::p1Stats.Chunli.wins, SF2Stats::p1Stats.Chunli.draws, SF2Stats::p1Stats.Chunli.loses, SF2Stats::p1Stats.Chunli.SPKO);
		break;
	case 6:
		DrawStats(c1FirstDigitPos, SF2Stats::p1Stats.Zanguief.wins, SF2Stats::p1Stats.Zanguief.draws, SF2Stats::p1Stats.Zanguief.loses, SF2Stats::p1Stats.Zanguief.SPKO);
		break;
	case 7:
		DrawStats(c1FirstDigitPos, SF2Stats::p1Stats.Dalshim.wins, SF2Stats::p1Stats.Dalshim.draws, SF2Stats::p1Stats.Dalshim.loses, SF2Stats::p1Stats.Dalshim.SPKO);
		break;
	default:
		break;
	}

	DrawStats(p1FirstDigitPos, SF2Stats::p1Stats.wins, SF2Stats::p1Stats.draws, SF2Stats::p1Stats.loses, SF2Stats::p1Stats.SPKO);

	switch (p2Selection)
	{
	case 0:
		DrawStats(c2FirstDigitPos, SF2Stats::p2Stats.Ryu.wins, SF2Stats::p2Stats.Ryu.draws, SF2Stats::p2Stats.Ryu.loses, SF2Stats::p2Stats.Ryu.SPKO);
		break;
	case 1:
		DrawStats(c2FirstDigitPos, SF2Stats::p2Stats.Honda.wins, SF2Stats::p2Stats.Honda.draws, SF2Stats::p2Stats.Honda.loses, SF2Stats::p2Stats.Honda.SPKO);
		break;
	case 2:
		DrawStats(c2FirstDigitPos, SF2Stats::p2Stats.Blanka.wins, SF2Stats::p2Stats.Blanka.draws, SF2Stats::p2Stats.Blanka.loses, SF2Stats::p2Stats.Blanka.SPKO);
		break;
	case 3:
		DrawStats(c2FirstDigitPos, SF2Stats::p2Stats.Guile.wins, SF2Stats::p2Stats.Guile.draws, SF2Stats::p2Stats.Guile.loses, SF2Stats::p2Stats.Guile.SPKO);
		break;
	case 4:
		DrawStats(c2FirstDigitPos, SF2Stats::p2Stats.Ken.wins, SF2Stats::p2Stats.Ken.draws, SF2Stats::p2Stats.Ken.loses, SF2Stats::p2Stats.Ken.SPKO);
		break;
	case 5:
		DrawStats(c2FirstDigitPos, SF2Stats::p2Stats.Chunli.wins, SF2Stats::p2Stats.Chunli.draws, SF2Stats::p2Stats.Chunli.loses, SF2Stats::p2Stats.Chunli.SPKO);
		break;
	case 6:
		DrawStats(c2FirstDigitPos, SF2Stats::p2Stats.Zanguief.wins, SF2Stats::p2Stats.Zanguief.draws, SF2Stats::p2Stats.Zanguief.loses, SF2Stats::p2Stats.Zanguief.SPKO);
		break;
	case 7:
		DrawStats(c2FirstDigitPos, SF2Stats::p2Stats.Dalshim.wins, SF2Stats::p2Stats.Dalshim.draws, SF2Stats::p2Stats.Dalshim.loses, SF2Stats::p2Stats.Dalshim.SPKO);
		break;
	default:
		break;
	}

	DrawStats(p2FirstDigitPos, SF2Stats::p2Stats.wins, SF2Stats::p2Stats.draws, SF2Stats::p2Stats.loses, SF2Stats::p2Stats.SPKO);
}

void Scene2PCharacterSelection::DrawStats(const fPoint & firstDigitPos, unsigned int wins, unsigned int draws, unsigned int loses, unsigned int spKO) const
{
	int firstDigit, secondDigit;
	fPoint currentPos = firstDigitPos;
	const Sprite* firstNumSprite;
	const Sprite* secondNumSprite;

	//Wins
	firstDigit = (int)(wins / 10);
	if (firstDigit > 0)
	{
		firstNumSprite = numbers[firstDigit];
		servicesManager->render->BlitGUI(texture, firstNumSprite->GetRectPosition(currentPos), firstNumSprite->rect);
	}
	currentPos.x += 8;
	secondDigit = wins % 10;
	secondNumSprite = numbers[secondDigit];
	servicesManager->render->BlitGUI(texture, secondNumSprite->GetRectPosition(currentPos), secondNumSprite->rect);

	//Loses
	currentPos.x += numberHDistance;
	firstDigit = (int)(loses / 10);
	if (firstDigit > 0)
	{
		firstNumSprite = numbers[firstDigit];
		servicesManager->render->BlitGUI(texture, firstNumSprite->GetRectPosition(currentPos), firstNumSprite->rect);
	}
	currentPos.x += 8;
	secondDigit = loses % 10;
	secondNumSprite = numbers[secondDigit];
	servicesManager->render->BlitGUI(texture, secondNumSprite->GetRectPosition(currentPos), secondNumSprite->rect);

	//Draws
	currentPos.x += numberHDistance;
	firstDigit = (int)(draws / 10);
	if (firstDigit > 0)
	{
		firstNumSprite = numbers[firstDigit];
		servicesManager->render->BlitGUI(texture, firstNumSprite->GetRectPosition(currentPos), firstNumSprite->rect);
	}
	currentPos.x += 8;
	secondDigit = draws % 10;
	secondNumSprite = numbers[secondDigit];
	servicesManager->render->BlitGUI(texture, secondNumSprite->GetRectPosition(currentPos), secondNumSprite->rect);

	//Special KO
	currentPos.x -= 8;
	currentPos.y += numberVDistance;
	firstDigit = (int)(spKO / 10);
	if (firstDigit > 0)
	{
		firstNumSprite = numbers[firstDigit];
		servicesManager->render->BlitGUI(texture, firstNumSprite->GetRectPosition(currentPos), firstNumSprite->rect);
	}
	currentPos.x += 8;
	secondDigit = spKO % 10;
	secondNumSprite = numbers[secondDigit];
	servicesManager->render->BlitGUI(texture, secondNumSprite->GetRectPosition(currentPos), secondNumSprite->rect);
}

void Scene2PCharacterSelection::DrawCursor(int selection, const Animation& animation) const
{
	fPoint position = playerFirstPos;

	if (selection < 4)
		position.x += (24 * selection);
	else
	{
		position.x += (24 * (selection - 4));
		position.y += 32;
	}

	if(!validCharacters[selection])
		servicesManager->render->BlitGUI(texture, forbbiden.GetRectPosition(position), forbbiden.rect);

	servicesManager->render->BlitGUI(texture, animation.GetFrame().GetRectPosition(position), animation.GetFrame().rect);
}
