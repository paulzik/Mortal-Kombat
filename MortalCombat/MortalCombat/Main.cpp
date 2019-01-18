#include <SDL.h>        
#include <SDL_image.h>
#include "LayerRenderer/LayerRenderer.h"
#include "Fighter/Fighter.h"
#include "UI/UIManager.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 508

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window * window = SDL_CreateWindow("Mortal Kombat 1 (1992)",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Rect button_pos = {42,58,163*2,12*2};
	SDL_Rect button_pos2 = { 412,58,163 * 2,12 * 2 };

	LayerRenderer* layerRenderer = new LayerRenderer(renderer);
	
	//Back Template
	layerRenderer->InitializeImageElement("./Bitmaps/BattleElements/template.png", LayerRenderer::Layer::Background, { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT});
	
	//Generate 2 Players
	Fighter* player1 = new Fighter(FighterTag::Scorpion,0);
	Fighter* player2 = new Fighter(FighterTag::SubZero,1);

	UIManager::Get()->InitializeCurrentScene(renderer);
	BattleUI* bat = new BattleUI(renderer);

	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		bat->RenderUI();

		//Render all 3 layers
		//layerRenderer->RenderLayer(LayerRenderer::Layer::Background);
		//layerRenderer->RenderLayer(LayerRenderer::Layer::Action);
		//layerRenderer->RenderLayer(LayerRenderer::Layer::Foreground);
		
		SDL_RenderPresent(renderer);
	}

	layerRenderer->ClearLayerRenderer();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}