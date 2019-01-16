#include <stdio.h>
#include <SDL.h>
#include "Configuration/JSONParser/json/json.h"
#include "Configuration/ConfigAPI.h"
#include <iostream>
#include <fstream>
#include "SoundEngine/SoundEngine.h"

using namespace std;
int main(int argc, char* argv[]) {
	SDL_Window* window;
	SDL_Renderer* renderer;

	//ConfigAPI* configAPI = new ConfigAPI("ConfigurationFile.json");
	//configAPI->ExportConfigurationData();
	
	SoundEngine::Get()->Play("../MortalCombat/SoundEngine/Sounds/announcer/fight.mp3",true);

	//list<ConfigAPI*> configAPIs = ConfigAPIs::Get();
	
	/*
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;

	// Create the window where we will draw.
	window = SDL_CreateWindow("SDL TEST WINDOW",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512,
		0);

	// We must call SDL_CreateRenderer in order for draw calls to affect this window.
	renderer = SDL_CreateRenderer(window, -1, 0);

	// Select the color for drawing. It is set to red here.
	SDL_SetRenderDrawColor(renderer, 50, 100, 150, 255);

	// Clear the entire screen to our selected color.
	SDL_RenderClear(renderer);

	// Up until now everything was drawn behind the scenes.
	// This will show the new, red contents of the window.
	SDL_RenderPresent(renderer);

	// Give us time to see the window.
	SDL_Delay(5000);

	// Always be sure to clean up
	SDL_Quit();
	
	*/
	system("pause");
	return 0;
}