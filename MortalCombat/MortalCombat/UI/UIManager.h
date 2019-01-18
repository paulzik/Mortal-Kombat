#pragma once
#include "BattleUI.h"
#include <SDL.h>        
#include <vector>
#include <SDL_image.h>

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

	static void RenderScene();
	static SDL_Renderer* GetRenderer();
private:
	//static BattleUI* battleScene;

	static UIManager* instance;
	static BattleUI* GetBattleUI();
	static BattleUI* battleScene;
	static void DisplayScene(SceneTag sceneTag);
	
};

