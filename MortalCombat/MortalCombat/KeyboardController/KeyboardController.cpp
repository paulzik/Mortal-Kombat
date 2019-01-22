#include "KeyboardController.h"
#include "../../Libraries/include/SDL.h"
#include <iostream>
#include "../UI/UIManager.h"
KeyboardController::KeyboardController()
{
	optionsOpen = false;
	optionsUP = optionsDown = false;
}

void KeyboardController::Update()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (!optionsOpen) {
					//if (UIManager::currentScene->GetSceneTag() == SceneTag::Battle) {
						UIManager::Get()->SetScene(SceneTag::Options);
					//}
					//else if (UIManager::currentScene->GetSceneTag() == SceneTag::Options) {
					//	UIManager::Get()->SetScene(SceneTag::Battle);
					//}
					optionsOpen = true;
				}
				break;
			case SDLK_w:
				UIManager::Get()->currentScene->InvokeMethod("w");
				break;
			case SDLK_s:
				UIManager::Get()->currentScene->InvokeMethod("s");
				break;
			case SDLK_a:
				UIManager::Get()->currentScene->InvokeMethod("a");
				break;
			case SDLK_d:
				UIManager::Get()->currentScene->InvokeMethod("d");
				break;
			default:
				break;
			}
		}
		else
		{
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (optionsOpen) {
				

					optionsOpen = false;
					break;
				}
				else {
					
				}
			default:
				break;
		}

	}


}
