#pragma once
#include "BattleUI.h"
#include <SDL.h>        
#include <vector>
#include <SDL_image.h>

using namespace std;

class UIManager
{
public:
	UICanvas* currentScene;
	static UIManager* Get(void);
	static void InitializeCurrentScene(SDL_Renderer* _renderer);

private:
	vector<UICanvas> sceneList;

	static UIManager* instance;
	static BattleUI* GetBattleUI();
	
};

