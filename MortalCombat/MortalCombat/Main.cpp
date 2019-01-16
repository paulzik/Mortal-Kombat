#include <SDL.h>        
#include <SDL_image.h>
#include "LayerRenderer/LayerRenderer.h"
#include "Configuration/JSONParser/json/json.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Animator/SDL_Helper.h"
#include "Animator/Sprites/AnimationFilms/AnimationFilmHolder.h"
#include "Animator/Animator/FrameRangeAnimator.h"
#include "Animator/AnimationTypes/MovingAnimation.h"
#include "Animator/Animator/AnimatorHolder.h"
#include "Fighter/Fighter.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 508

AnimationFilmHolder* AFH;
AnimatorHolder* animator;
typedef std::map<std::string, Animator*> Animators;
Animators* animators;

Sprite* scorpion;

void InitializeCharacter(std::string _charName, SDL_Renderer * renderer) {
	if (_charName == "subzero") {
		AFH = new AnimationFilmHolder();
		AFH->Load("./Bitmaps/Clips/Scorpion/Scorpion", renderer);

		//TODO: check json for animators

		scorpion = new Sprite(0, 0, AFH->GetFilm("Idle"));
		animators = new Animators();
		animators->insert(std::pair<std::string, Animator*>("idle", new FrameRangeAnimator()));
		animators->insert(std::pair<std::string, Animator*>("walk", new FrameRangeAnimator()));
		animators->insert(std::pair<std::string, Animator*>("walkReverse", new FrameRangeAnimator()));
		animators->insert(std::pair<std::string, Animator*>("punchrighthigh", new FrameRangeAnimator()));
		animators->at("punchrighthigh")->SetOnFinish([](Animator*, void*) {
			ToBeRunning = animators->at("idle");
			ToBeSuspended = animators->at("punchrighthigh");
			scorpion->SetAnimFilm(AFH->GetFilm("Idle"));
			//direction = MOVE_DIR::none;
		});

		std::map<std::string, Animation*> animations;
		animations.insert(std::pair<std::string, Animation*>("idle", new FrameRangeAnimation(0, 6, 0, 0, 0.075f, true, 1)));
		animations.insert(std::pair<std::string, Animation*>("walk", new FrameRangeAnimation(0, 8, 4, 0, 0.075f, true, 0)));
		animations.insert(std::pair<std::string, Animation*>("walkReverse", new FrameRangeAnimation(0, 8, -4, 0, 0.075f, true, 0)));
		animations.insert(std::pair<std::string, Animation*>("punchrighthigh", new FrameRangeAnimation(0, 2, 0, 0, 0.5f, false, 2)));

		float time = clock() / CLOCKS_PER_SEC;
		for (auto entry : *animators) {
			((FrameRangeAnimator*)entry.second)->Start(scorpion, (FrameRangeAnimation*)animations.at(entry.first), time);
			animator->Register(entry.second);
		}
	}
}

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
	
	//LifeBars -- TODO: Will be otimized as they are the same texture
	layerRenderer->InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", LayerRenderer::Layer::Foreground, { 42,58,163 * 2,12 * 2 });
	layerRenderer->InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", LayerRenderer::Layer::Foreground, { 412,58,163 * 2,12 * 2 });

	//Generate 2 Players
	Fighter* player1 = new Fighter(FighterTag::Scorpion);
	Fighter* player2 = new Fighter(FighterTag::SubZero);

	InitializeCharacter("subzero", renderer);
	animator->MarkAsRunning(animators->at("idle"));

	while (!quit)
	{
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		

		//Render all 3 layers
		layerRenderer->RenderLayer(LayerRenderer::Layer::Background);
		layerRenderer->RenderLayer(LayerRenderer::Layer::Action);
		layerRenderer->RenderLayer(LayerRenderer::Layer::Foreground);
		
		animator->Progress(float((float)clock() / (float)CLOCKS_PER_SEC));

		animator->Render(renderer);

		SDL_RenderPresent(renderer);
	}

	layerRenderer->ClearLayerRenderer();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}