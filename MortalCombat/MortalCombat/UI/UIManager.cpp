#include "UIManager.h"

UIManager* UIManager::instance;

UIManager* UIManager::Get() {
	if (!instance) {
		//Initialize UI Manager

		instance = new UIManager;
	}

	return instance;
}
void UIManager::InitializeCurrentScene(SDL_Renderer* _renderer)
{ 
	//currentScene

};
