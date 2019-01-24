#include "KeyboardController.h"
#include "../../Libraries/include/SDL.h"
#include <iostream>
#include "../UI/UIManager.h"
#include "../Configuration/ConfigAPIs.h"
#include "../SoundEngine/SoundEngine.h"

KeyboardController::KeyboardController()
{
	optionsOpen = false;
	optionsUP = optionsDown = false;
}

void KeyboardController::Update(Fighter* _p1, Fighter* _p2)
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				if (!optionsOpen) {
					UIManager::Get()->ToggleGamePause();
					if (UIManager::Get()->currentScene->GetSceneTag() == SceneTag::Battle) {
						UIManager::Get()->SetScene(SceneTag::Options);
						SoundEngine::Get()->Play("./SoundEngine/Sounds/ui/GamePause.mp3");
					}
					else if (UIManager::Get()->currentScene->GetSceneTag() == SceneTag::Options) {
						UIManager::Get()->SetScene(SceneTag::Battle);
						//Save and Apply Changes (Configurations)
						ConfigAPIs::Get().front()->ExportConfigurationData();
					}
					optionsOpen = true;
				}
				break;
			case SDLK_SPACE:
				if (UIManager::Get()->currentScene->GetSceneTag() == SceneTag::Welcome) {
					UIManager::Get()->SetScene(SceneTag::Battle);
				}
				else if (UIManager::Get()->currentScene->GetSceneTag() == SceneTag::Battle) {
					UIManager::reset = true;
					//UIManager::Get()->SetScene(SceneTag::Welcome);
				}
				break;
			case SDLK_w:
				UIManager::Get()->currentScene->InvokeMethod("w");
				AddKey(_p1, "w");
				break;
			case SDLK_s:
				UIManager::Get()->currentScene->InvokeMethod("s");
				AddKey(_p1, "s");
				break;
			case SDLK_a:
				UIManager::Get()->currentScene->InvokeMethod("a");
				AddKey(_p1, "a");
				break;
			case SDLK_d:
				UIManager::Get()->currentScene->InvokeMethod("d");
				AddKey(_p1, "d");
				break;
			case SDLK_q:
				AddKey(_p1, "q");
				break;
			case SDLK_3:
				AddKey(_p1, "3");
				break;
			case SDLK_4:
				AddKey(_p1, "4");
				break;
			case SDLK_5:
				AddKey(_p1, "5");
				break;
			case SDLK_6:
				AddKey(_p1, "6");
				break;

			//Player2
			case SDLK_i:
				AddKey(_p2, "i");
				break;
			case SDLK_k:
				AddKey(_p2, "k");
				break;
			case SDLK_j:
				AddKey(_p2, "j");
				break;
			case SDLK_l:
				AddKey(_p2, "l");
				break;
			case SDLK_7:
				AddKey(_p2, "7"); //high punch
				break;
			case SDLK_8:
				AddKey(_p2, "8"); // low punch
				break;
			case SDLK_9:
				AddKey(_p2, "9"); //high kick
				break;
			case SDLK_0:
				AddKey(_p2, "0"); //low kick
				break;
			case SDLK_o:
				AddKey(_p2, "o"); //low kick
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
				break;
			//Player1
			case SDLK_w:
				//UIManager::Get()->currentScene->InvokeMethod("w");
				RemoveKey(_p1, "w");
				break;
			case SDLK_s:
				//UIManager::Get()->currentScene->InvokeMethod("s");
				RemoveKey(_p1, "s");
				break;
			case SDLK_a:
				//UIManager::Get()->currentScene->InvokeMethod("a");
				RemoveKey(_p1, "a");
				break;
			case SDLK_d:
				//UIManager::Get()->currentScene->InvokeMethod("d");
				RemoveKey(_p1, "d");
				break;
			case SDLK_q:
				RemoveKey(_p1, "q");
				break;

			//Player2
			case SDLK_i:
				//UIManager::Get()->currentScene->InvokeMethod("w");
				RemoveKey(_p2, "i");
				break;
			case SDLK_k:
				//UIManager::Get()->currentScene->InvokeMethod("s");
				RemoveKey(_p2, "k");
				break;
			case SDLK_j:
				//UIManager::Get()->currentScene->InvokeMethod("a");
				RemoveKey(_p2, "j");
				break;
			case SDLK_l:
				//UIManager::Get()->currentScene->InvokeMethod("d");
				RemoveKey(_p2, "l");
				break;
			case SDLK_o:
				//UIManager::Get()->currentScene->InvokeMethod("d");
				RemoveKey(_p2, "o");
				break;
			default:
				break;
		}

	}


}

void KeyboardController::AddKey(Fighter* _fighter, std::string _key)
{
	if (UIManager::Get()->IsGamePaused() || UIManager::Get()->KeyBoardBlocked())
		return;
	if (_key == "d" || _key == "s" || _key == "a" || _key == "w" || _key == "i" || _key == "l" || _key == "k" || _key == "j" || _key == "q" || _key == "o") {
		_fighter->AddMove(_key);
	}
	else
		_fighter->AddKey(_key);
}

void KeyboardController::RemoveKey(Fighter * _fighter, std::string _key)
{
	if (UIManager::Get()->IsGamePaused() || UIManager::Get()->KeyBoardBlocked())
		return;
	if (_key == "d" || _key == "s" || _key == "a" || _key == "w" || _key == "i" || _key == "l" || _key == "k" || _key == "j" || _key == "q" || _key == "o") {
		_fighter->RemoveMove(_key);
	}
	else
		_fighter->AddKey(_key);
}
