#pragma once
#include <SDL.h>        
#include <SDL_image.h>
#include "LayerRenderer/LayerRenderer.h"
#include "Configuration/JSONParser/json/json.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Animator/SDL_Helper.h"
#include "Fighter/Fighter.h"
#include "UI/UIManager.h"
#include "HorizonLayer/HorizonLayer.h"
#include "SoundEngine\SoundEngine.h"
#include "KeyboardController/KeyboardController.h"
#include "Configuration\ConfigAPIs.h"
#include "Animator/Animator/AnimatorHolder.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 508

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;
	AnimatorHolder::clap = false;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window * window = SDL_CreateWindow("Mortal Kombat 1 (1992)",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	HorizonLayer hl(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Rect button_pos = {42,58,163*2,12*2};
	SDL_Rect button_pos2 = { 412,58,163 * 2,12 * 2 };

	LayerRenderer* layerRenderer = new LayerRenderer(renderer);
	
	//Configuration Initial setup
	ConfigAPI* configAPI = new ConfigAPI("ConfigurationFile.json");
	ConfigAPIs::Add(configAPI);

	ConfigAPIs::Get().front()->SetBetWinMode(0);
	ConfigAPIs::Get().front()->SetPlayerWins(1, 0);
	ConfigAPIs::Get().front()->SetPlayerWins(2, 0);
	

while (!UIManager::Get()->ExitApp) {
		//Generate 2 Players
		Fighter* player1 = new Fighter(FighterTag::Scorpion, PlayerIndex::P1, renderer);
		Fighter* player2 = new Fighter(FighterTag::SubZero, PlayerIndex::P2, renderer);
		player1->SetOpponent(player2);
		player2->SetOpponent(player1);
		player1->InitializeStateMachineScorpion(player1->GetState());
		player2->InitializeStateMachineSubZero(player2->GetState());
		//Initialize scenes
		UIManager::Get()->InitializeManager(renderer);
		UIManager::Get()->InitializeBattleScene(player1, player2);
		UIManager::Get()->InitializeWelcomeScene();
		UIManager::Get()->InitializeOptionsScene();
		if (!UIManager::reset)
			UIManager::Get()->SetScene(SceneTag::Welcome);
		else
			UIManager::Get()->SetScene(SceneTag::Battle);
		UIManager::reset = false;

		KeyboardController* keyboardController = new KeyboardController();

		while (!quit)
		{
			//keyboardController->Update();
			//Render all 3 layers
			SDL_RenderClear(renderer);
			if (!UIManager::Get()->IsGamePaused()) {
				layerRenderer->RenderLayer(LayerRenderer::Layer::Action);
				player1->Update();
				player2->Update();
				player1->FlipCharacter(player1->positionX < player2->positionX ? true : false);
				player2->FlipCharacter(player1->positionX < player2->positionX ? false : true);

				AnimatorHolder::Progress(float((float)clock() / (float)CLOCKS_PER_SEC));
				AnimatorHolder::Render(renderer);
			}

			layerRenderer->RenderLayer(LayerRenderer::Layer::Foreground);

			UIManager::Get()->RenderScene();

			keyboardController->Update(player1, player2);

			SDL_RenderPresent(renderer);
			if (player1->GetHealth() <= 0 || player2->GetHealth() <= 0)
			{
				AnimatorHolder::clap = true;
			}

			if ((player1->GetHealth() <= 0 || player2->GetHealth() <= 0) && UIManager::Get()->reset) {
				player1->StopAll();
				player2->StopAll();
				UIManager::Get()->currentScene->KillAnimation("scorpionwins");
				UIManager::Get()->currentScene->KillAnimation("subzerowins");
				AnimatorHolder::clap = false;
				//AnimatorHolder::Cancel(hl.animators->at("h2"));
				break;
			}
			if (UIManager::Get()->ExitApp) break;
		}

	}
	SoundEngine::Get()->DeleteSoundEngine();
	layerRenderer->ClearLayerRenderer();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	ConfigAPIs::Get().front()->SetPlayerWins(1, 0);
	ConfigAPIs::Get().front()->SetPlayerWins(2, 0);

	ConfigAPIs::Get().front()->SetBetWinMode(0);
	ConfigAPIs::Get().front()->ExportConfigurationData();

	return 0;
}