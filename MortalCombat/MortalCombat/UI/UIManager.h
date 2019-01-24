#pragma once
#include "BattleUI.h"
#include <SDL.h>        
#include <vector>
#include <SDL_image.h>
#include "OptionsUI.h"
#include "WelcomeUI.h"

using namespace std;

enum SceneTag { Welcome, Battle, Options };

class UIManager
{
public:
	static UICanvas* currentScene;
	static UIManager* Get(void);
	static SDL_Renderer* renderer;
	static void InitializeManager(SDL_Renderer* _renderer);
	static void InitializeBattleScene(Fighter* player1, Fighter* player2);
	static void InitializeWelcomeScene();
	static void InitializeOptionsScene();
	static void SetScene(SceneTag scene);
	static bool IsGamePaused();
	static void ToggleGamePause();
	static bool KeyBoardBlocked();
	static void BlockKeyboard();
	static void RenderScene();
	static void ResetTimer();
	static SDL_Renderer* GetRenderer();
	static bool reset;

	static void FireAnimation(string animationNamde, int destroytime);
private:
	static bool paused;
	static bool keyboardBlocked;
	static UIManager* instance;
	static BattleUI* battleScene;
	static OptionsUI* optionsScene;
	static WelcomeUI* welcomeScene;
	static void DisplayScene(SceneTag sceneTag);
	static int  startTimer, stopAnimationTime;
	static string animationToKill;

};

