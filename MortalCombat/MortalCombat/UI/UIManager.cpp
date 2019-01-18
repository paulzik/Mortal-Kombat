#include "UIManager.h"

UIManager* UIManager::instance;
SDL_Renderer* UIManager::renderer;
BattleUI* UIManager::battleScene;
OptionsUI* UIManager::optionsScene;

UIManager* UIManager::Get() {
	if (!instance) {
		//Initialize UI Manager

		instance = new UIManager;
	}

	return instance;
}
void UIManager::InitializeManager(SDL_Renderer* _renderer)
{ 
	//SelectScene(SceneTag::Welcome);
	renderer = _renderer;
}

void UIManager::InitializeBattleScene(Fighter* player1, Fighter* player2)
{
	battleScene = new BattleUI(player1, player2);
}

void UIManager::InitializeWelcomeScene()
{

}

void UIManager::InitializeOptionsScene()
{
}

void UIManager::RenderScene()
{
	battleScene->RenderUI();
}

void UIManager::DisplayScene(SceneTag sceneTag)
{
	
}
SDL_Renderer * UIManager::GetRenderer()
{
	return renderer;
}
;
