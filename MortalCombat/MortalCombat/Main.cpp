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
#include "Arena/Arena.h"
#include "HorizonLayer/HorizonLayer.h"
#include "SoundEngine\SoundEngine.h"
#include "KeyboardController/KeyboardController.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 508


int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window * window = SDL_CreateWindow("Mortal Kombat 1 (1992)",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	HorizonLayer hl(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Rect button_pos = {42,58,163*2,12*2};
	SDL_Rect button_pos2 = { 412,58,163 * 2,12 * 2 };

	LayerRenderer* layerRenderer = new LayerRenderer(renderer);
	
	//Back Template
	layerRenderer->InitializeImageElement("./Bitmaps/BattleElements/template.png", LayerRenderer::Layer::Background, { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT});
	
	//LifeBars -- TODO: Will be otimized as they are the same texture
	//layerRenderer->InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", LayerRenderer::Layer::Foreground, { 42,58,163 * 2,12 * 2 });
	//layerRenderer->InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", LayerRenderer::Layer::Foreground, { 412,58,163 * 2,12 * 2 });

	//Generate Arena
	Arena* arena = new Arena(renderer);
	//Generate 2 Players
	Fighter* player1 = new Fighter(FighterTag::Scorpion, PlayerIndex::P1, renderer);
	Fighter* player2 = new Fighter(FighterTag::SubZero, PlayerIndex::P2, renderer);
	//Initialize scenes
	UIManager::Get()->InitializeManager(renderer);
	UIManager::Get()->InitializeBattleScene(player1, player2);
	UIManager::Get()->InitializeWelcomeScene();
	UIManager::Get()->InitializeOptionsScene();
	//Setup Battle scene *Replace with welcome scene
	UIManager::Get()->SetScene(SceneTag::Battle);

	//SoundEngine::Get()->Play("./SoundEngine/Sounds/Mortal Kombat Theme Song Original.mp3", true);

	KeyboardController* keyboardController = new KeyboardController();

	while (!quit)
	{
		//keyboardController->Update();
		//Render all 3 layers
		SDL_RenderClear(renderer);
		hl.DisplayHorizon();
		//layerRenderer->RenderLayer(LayerRenderer::Layer::Background);

		layerRenderer->RenderLayer(LayerRenderer::Layer::Action);
		player1->Update();
		player2->Update();
		player1->FlipCharacter(player1->x < player2->x ? true : false);
		player2->FlipCharacter(player1->x < player2->x ? false : true);

		AnimatorHolder::Progress(float((float)clock() / (float)CLOCKS_PER_SEC));
		AnimatorHolder::Render(renderer);

		layerRenderer->RenderLayer(LayerRenderer::Layer::Foreground);

		UIManager::Get()->RenderScene();
		

		
		SDL_RenderPresent(renderer);
	}
	SoundEngine::Get()->DeleteSoundEngine();
	layerRenderer->ClearLayerRenderer();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}