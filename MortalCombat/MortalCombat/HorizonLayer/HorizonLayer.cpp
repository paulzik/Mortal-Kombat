#include "HorizonLayer.h"

#include <string>

bool HorizonLayer::ClippedEntirely(SDL_Rect& area, SDL_Rect& in, SDL_Rect* out)
{
	return true;
}


void HorizonLayer::InitializeHorizon(SDL_Renderer *renderer)
{
	int index = 1000;
	afh = new AnimationFilmHolder();
	sprites = new SpritesHolder();
	afh->Load("Horizon", renderer);
	
	for (int i = 0; i < TOTAL_HOBJECTS; ++i) //keep width and height in class for sprite. Load them from AFH
	{
		SDL_Rect box = afh->GetFilm("h" + std::to_string(i))->GetFrameBox(0);

		hRects[i].w = box.w;
		hRects[i].h = box.h;
		hRects[i].x = ((hRects[i].w - screen_w) / 2)*(-1);
	}
	hRects[0].y = 0;
	hRects[1].y = 0;
	hRects[2].y = screen_h - hRects[2].h*1.5;
	hRects[3].y = screen_h - hRects[3].h;
	hRects[4].y = screen_h - hRects[4].h;


	animators = new Animators();
	animators->insert(std::pair<std::string, Animator*>("h0", new FrameRangeAnimator(index++)));
	animators->insert(std::pair<std::string, Animator*>("h1", new FrameRangeAnimator(index++)));
	animators->insert(std::pair<std::string, Animator*>("h2", new FrameRangeAnimator(index++)));
	animators->insert(std::pair<std::string, Animator*>("h3", new FrameRangeAnimator(index++)));
	animators->insert(std::pair<std::string, Animator*>("h4", new FrameRangeAnimator(index++)));

	index = 1000;
	std::map<std::string, Animation*> animations;
	animations.insert(std::pair<std::string, Animation*>("h0", new FrameRangeAnimation(0, 1, 0, 0, 0.2f, true, index++)));
	animations.insert(std::pair<std::string, Animation*>("h1", new FrameRangeAnimation(0, 1, 0, 0, 0.2f, true, index++)));
	animations.insert(std::pair<std::string, Animation*>("h2", new FrameRangeAnimation(0, 3, 0, 0, 0.2f, true, index++)));
	animations.insert(std::pair<std::string, Animation*>("h3", new FrameRangeAnimation(0, 1, 0, 0, 0.2f, true, index++)));
	animations.insert(std::pair<std::string, Animation*>("h4", new FrameRangeAnimation(0, 1, 0, 0, 0.2f, true, index++)));




	float time = clock() / CLOCKS_PER_SEC;
	int i = 0;
	for (auto entry : *animators)
	{
		AnimationFilm* af = new AnimationFilm(*afh->GetFilm("h"+ std::to_string(i)));

		Sprite *s = new Sprite(hRects[i].x, hRects[i].y, af, flipped);
		((FrameRangeAnimator*)entry.second)->Start(s, (FrameRangeAnimation*)animations.at(entry.first), time, true);

		AnimatorHolder::Register(entry.second);
		AnimatorHolder::MarkAsRunning(animators->at("h" + std::to_string(i)));
		sprites->Add(s, 0);
		++i;
	}

}

HorizonLayer::HorizonLayer(SDL_Renderer* _renderer, int sw, int sh)
{
	renderer = _renderer;
	flipped = false;
	screen_w = sw;
	screen_h = sh;

	InitializeHorizon(renderer);
}


HorizonLayer::~HorizonLayer()
{
}
