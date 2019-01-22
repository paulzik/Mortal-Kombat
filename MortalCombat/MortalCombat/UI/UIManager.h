#pragma once
#include "BattleUI.h"
#include <SDL.h>        
#include <vector>
#include <SDL_image.h>
#include "OptionsUI.h"

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
	static void RenderScene();
	static SDL_Renderer* GetRenderer();
private:
	//static BattleUI* battleScene;

	static UIManager* instance;
	static BattleUI* battleScene;
	static OptionsUI* optionsScene;
	static void DisplayScene(SceneTag sceneTag);
	
};

