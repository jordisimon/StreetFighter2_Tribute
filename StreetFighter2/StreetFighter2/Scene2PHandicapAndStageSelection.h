#pragma once
#include "Scene.h"
#include "SceneMatchInfo.h"
#include "Color.h"
#include "Point.h"
#include "Sprite.h"
#include <vector>

struct SDL_Texture;
class CommandContext;

class Scene2PHandicapAndStageSelection : public Scene
{
private:
	enum class StageSelectionState
	{
		HANDICAP,
		STAGE
	};

	SceneMatchInfo matchInfo;

	Color bgColor;
	Color fadeColor;

	const char* configSection;
	SDL_Texture* texture = nullptr;

	CommandContext* commandContextMenu = nullptr;

	unsigned int p1Handicap;
	unsigned int p2Handicap;
	int stageSelection;

	StageSelectionState currentState;

	Sprite handicapStageSelection;
	fPoint handicapStageSelectionPos;

	Sprite RyuBigPortrait;
	Sprite HondaBigPortrait;
	Sprite BlankaBigPortrait;
	Sprite GuileBigPortrait;
	Sprite KenBigPortrait;
	Sprite ChunliBigPortrait;
	Sprite ZanguiefBigPortrait;
	Sprite DalshimBigPortrait;

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

	std::vector<bool> validStages;

	fPoint p1PortraitPos;
	fPoint p1NamePos;

	fPoint p2PortraitPos;
	fPoint p2NamePos;

	Sprite handicap;
	fPoint handicapPos;

	Sprite stageSelect;
	fPoint stageSelectPos;

	Sprite red0;
	Sprite red1;
	Sprite red2;
	Sprite red3;
	Sprite red4;
	Sprite red5;
	Sprite red6;
	Sprite red7;

	std::vector<Sprite*> numbers;

	fPoint handicapFirstPosP1;
	fPoint handicapFirstPosP2;

	Sprite forbbiden;

	Sprite japanFlag;
	Sprite brazilFlag;
	Sprite USAFlag;
	Sprite chinaFlag;
	Sprite USSRFlag;
	Sprite indiaFlag;
	Sprite thailandFlag;
	Sprite spainFlag;

	std::vector<Sprite*> flags;

	fPoint flagFirstPos;

	Sprite RyuStageName;
	Sprite HondaStageName;
	Sprite BlankaStageName;
	Sprite GuileStageName;
	Sprite KenStageName;
	Sprite ChunliStageName;
	Sprite ZanguiefStageName;
	Sprite DalshimStageName;
	Sprite BisonStageName;
	Sprite SagatStageName;
	Sprite BalrogStageName;
	Sprite VegaStageName;

	std::vector<Sprite*> stageNames;

	fPoint stageNamePos;

	void FillStageInfoAndSceneChange();

	void DrawHandicap(int handicap, const fPoint& initialPos) const;
	void DrawFlag() const;
	
public:
	Scene2PHandicapAndStageSelection(const SceneMatchInfo& info);
	~Scene2PHandicapAndStageSelection();

	bool Init();
	bool CleanUp();

	bool Start();

	bool ProcessInput(CommandData* commandData);
	Entity::Result UpdateState();
	Entity::Result Draw() const;
};

