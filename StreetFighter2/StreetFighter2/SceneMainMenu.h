#pragma once
#include "Scene.h"
#include "Point.h"
#include "Sprite.h"
#include "Animation.h"
#include "Timer.h"

struct SDL_Texture;
class CommandContext;

class SceneMainMenu : public Scene
{
private:
	enum class MainMenuState
	{
		INTRO_WAIT,
		LOGO_SPIN,
		TWW_IN,
		SCENE_COMPLETED,
		SHOW_MENU
	};

	const char* configSection;
	SDL_Texture* texture = nullptr;
	const char* configSectionAnim;
	SDL_Texture* textureAnim = nullptr;

	static int optionMoveSfx;
	static int optionSelectSfx;

	CommandContext* commandContextMenu = nullptr;

	bool firstStart;
	MainMenuState currentState;
	MainMenuState nextState;

	Animation SFLogoAnim;
	Sprite SFLogo;
	fPoint SFLogoPos;

	Sprite tww1;
	Sprite tww2;
	fPoint tww1CurrentPos;
	fPoint tww2CurrentPos;
	fPoint twwFinalPos;
	float twwIntroSpeed;

	Sprite capcomInfo;
	fPoint capcomInfoPos;

	Sprite options;
	fPoint optionsPos;

	Sprite cursor;
	fPoint cursorPos;

	Timer timer;

public:
	SceneMainMenu(bool showMenu = false);
	~SceneMainMenu();

	bool Init();
	bool CleanUp();

	bool Start();

	bool ProcessInput(CommandData* commandData);
	Entity::Result UpdateState();
	Entity::Result Draw() const;
};

