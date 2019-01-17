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

	SDL_Rect button_pos = {42,58,163*2,12*2};
	SDL_Rect button_pos2 = { 412,58,163 * 2,12 * 2 };

	LayerRenderer* layerRenderer = new LayerRenderer(renderer);
	
	//Back Template
	layerRenderer->InitializeImageElement("./Bitmaps/BattleElements/template.png", LayerRenderer::Layer::Background, { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT});
	
	//LifeBars -- TODO: Will be otimized as they are the same texture
	layerRenderer->InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", LayerRenderer::Layer::Foreground, { 42,58,163 * 2,12 * 2 });
	layerRenderer->InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", LayerRenderer::Layer::Foreground, { 412,58,163 * 2,12 * 2 });

	//Generate 2 Players
	Fighter* player1 = new Fighter(FighterTag::Scorpion, renderer);
	//Fighter* player2 = new Fighter(FighterTag::SubZero);

	while (!quit)
	{

		

		//Render all 3 layers
		layerRenderer->RenderLayer(LayerRenderer::Layer::Background);

		layerRenderer->RenderLayer(LayerRenderer::Layer::Action);
		player1->Update();

		layerRenderer->RenderLayer(LayerRenderer::Layer::Foreground);

		
		SDL_RenderPresent(renderer);
	}

	layerRenderer->ClearLayerRenderer();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}