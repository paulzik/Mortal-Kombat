#include "UIManager.h"
#include "../SoundEngine/SoundEngine.h"

UIManager* UIManager::instance;
SDL_Renderer* UIManager::renderer;
BattleUI* UIManager::battleScene;
OptionsUI* UIManager::optionsScene;
WelcomeUI* UIManager::welcomeScene;
UICanvas* UIManager::currentScene;
bool UIManager::paused;
bool UIManager::keyboardBlocked;
bool UIManager::reset;

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
	keyboardBlocked = false;
}

void UIManager::InitializeBattleScene(Fighter* player1, Fighter* player2)
{
	battleScene = new BattleUI(player1, player2);
}

void UIManager::InitializeWelcomeScene()
{
	welcomeScene = new WelcomeUI();
}

void UIManager::InitializeOptionsScene()
{
	optionsScene = new OptionsUI();
}

void UIManager::SetScene(SceneTag scene)
{
	if (scene == SceneTag::Battle) {
		//REMOVE COMMENTS FOR FINAL
		//if (currentScene->GetSceneTag() == SceneTag::Welcome) {
			SoundEngine::Get()->StopAllSounds();
			SoundEngine::Get()->Play("./SoundEngine/Sounds/BattleMusic1.mp3", true);
		//}
		currentScene = battleScene;
	}else if (scene == SceneTag::Welcome) {
		SoundEngine::Get()->Play("./SoundEngine/Sounds/Mortal Kombat Theme Song Original.mp3", true);
		currentScene = welcomeScene;
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

bool UIManager::KeyBoardBlocked()
{
	return keyboardBlocked;
}

void UIManager::BlockKeyboard()
{
}

void UIManager::RenderScene()
{
	currentScene->RenderUI();
}

void UIManager::DisplayScene(SceneTag sceneTag)
{
	
}
SDL_Renderer * UIManager::GetRenderer()
{
	return renderer;
}
;
