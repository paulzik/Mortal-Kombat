#include "UIManager.h"

UIManager* UIManager::instance;
SDL_Renderer* UIManager::renderer;
BattleUI* UIManager::battleScene;
OptionsUI* UIManager::optionsScene;
UICanvas* UIManager::currentScene;
bool UIManager::paused;

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
	paused = false;
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
	optionsScene = new OptionsUI();
}

void UIManager::SetScene(SceneTag scene)
{
	if (scene == SceneTag::Battle) {
		currentScene = battleScene;
	}else if (scene == SceneTag::Welcome) {
		//currentScene = welcomeScene;
	}else if (scene == SceneTag::Options) {
		currentScene = optionsScene;
	}
}

bool UIManager::IsGamePaused()
{
	return paused;
}

void UIManager::ToggleGamePause()
{
	paused = !paused;
}

void UIManager::RenderScene()
{
	currentScene->RenderUI();
	//optionsScene->RenderUI();
}

void UIManager::DisplayScene(SceneTag sceneTag)
{
	
}
SDL_Renderer * UIManager::GetRenderer()
{
	return renderer;
}
;
