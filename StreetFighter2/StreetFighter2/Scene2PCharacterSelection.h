#pragma once
#include "Scene.h"
#include "Color.h"
#include "Point.h"
#include "Sprite.h"
#include "Animation.h"
#include "CommandAction.h"
#include <vector>
#include "SceneMatchInfo.h"

struct SDL_Texture;
class CommandContext;

class Scene2PCharacterSelection : public Scene
{
private:
	SceneMatchInfo matchInfo;

	Color bgColor;

	const char* configSection;
	SDL_Texture* texture = nullptr;

	static int optionMoveSfx;
	static int characterConfirmSfx;

	int p1Selection;
	int p2Selection;
	bool p1Selected;
	bool p2Selected;

	CommandContext* commandContextMenu = nullptr;

	Sprite playerSelection;
	fPoint playerSelectionPos;

	Sprite forbbiden;

	Animation p1Cursor;
	Animation p2Cursor;

	fPoint playerFirstPos;

	Sprite RyuPortrait;
	Sprite HondaPortrait;
	Sprite BlankaPortrait;
	Sprite GuilePortrait;
	Sprite KenPortrait;
	Sprite ChunliPortrait;
	Sprite ZanguiefPortrait;
	Sprite DalshimPortrait;

	Sprite RyuName;
	Sprite HondaName;
	Sprite BlankaName;
	Sprite GuileName;
	Sprite KenName;
	Sprite ChunliName;
	Sprite ZanguiefName;
	Sprite DalshimName;

	std::vector<Sprite*> portraits;
	std::vector<Sprite*> names;
	//Only completed characters are suitable for selection
	std::vector<bool> validCharacters;

	fPoint p1PortraitPos;
	fPoint p1NamePos;

	fPoint p2PortraitPos;
	fPoint p2NamePos;

	Sprite white0;
	Sprite white1;
	Sprite white2;
	Sprite white3;
	Sprite white4;
	Sprite white5;
	Sprite white6;
	Sprite white7;
	Sprite white8;
	Sprite white9;

	std::vector<Sprite*> numbers;

	fPoint c1FirstDigitPos;
	fPoint p1FirstDigitPos;
	fPoint c2FirstDigitPos;
	fPoint p2FirstDigitPos;

	int numberHDistance;
	int numberVDistance;

	void FillCharacterInfoAndSceneChange();

	void DrawAllStats() const;
	void DrawStats(const fPoint& firstDigitPos, unsigned int wins, unsigned int draws, unsigned int loses, unsigned int spKO) const;

	void DrawCursor(int position, const Animation& animation) const;

public:
	Scene2PCharacterSelection(const SceneMatchInfo& info);
	~Scene2PCharacterSelection();

	bool Init();
	bool CleanUp();

	bool Start();

	bool ProcessInput(CommandData* commandData);
	Entity::Result UpdateState();
	Entity::Result Draw() const;
};

