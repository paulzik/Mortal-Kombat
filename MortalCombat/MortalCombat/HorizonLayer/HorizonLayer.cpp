#include "HorizonLayer.h"



bool HorizonLayer::ClippedEntirely(SDL_Rect& area, SDL_Rect& in, SDL_Rect* out)
{
	return true;
}


void HorizonLayer::DisplayHorizon()
{
	//SDL_Rect dstRect[5];
	//SDL_Rect srcRect[5];
	//Floor render
	for (int i = 0; i < TOTAL_HOBJECTS; i++)
	{
		if (i == 2)
		{
			continue;
		}
		if (screen_w >= hRects[i].w)
		{
			srcRect[i].w = hRects[i].w;
			srcRect[i].x = 0;
			dstRect[i].x = (screen_w - hRects[i].w) / 2;
		}
		else
		{
			srcRect[i].w = screen_w;
			srcRect[i].x = (hRects[i].w - screen_w)/2;
			dstRect[i].x = 0;
		}
		srcRect[i].h = hRects[i].h;
		dstRect[i].y = hRects[i].y;

		dstRect[i].w = srcRect[i].w;
		dstRect[i].h = srcRect[i].h;

		SDL_RenderCopy(renderer, hObjects[i], &srcRect[i], &dstRect[i]);
	}

}

void HorizonLayer::InitializeShaolins(SDL_Renderer *renderer)
{
	afh = new AnimationFilmHolder();
	sprites = new SpritesHolder();
	afh->Load("Shaolins", renderer);
	animators = new Animators();
	animators->insert(std::pair<std::string, Animator*>("h3", new FrameRangeAnimator(1000)));
	std::map<std::string, Animation*> animations;
	animations.insert(std::pair<std::string, Animation*>("h3", new FrameRangeAnimation(0, 2, 0, 0, 0.2f, true, 1000)));
	std::cout << "shaolins animations entered\n";
	float time = clock() / CLOCKS_PER_SEC;
	for (auto entry : *animators)
	{
		if (entry.first == "h3")
		{
			AnimationFilm* h3af = new AnimationFilm(*afh->GetFilm("h3"));
			std::cout << "got afh\n";
			Sprite *s = new Sprite(hRects[2].x, hRects[2].y, h3af, flipped);
			((FrameRangeAnimator*)entry.second)->Start(s, (FrameRangeAnimation*)animations.at(entry.first), time, true);
			std::cout << "before register\n";
			AnimatorHolder::Register(entry.second);
			AnimatorHolder::MarkAsRunning(animators->at("h3"));
			sprites->Add(s, 0);
		}
	}
	std::cout << "shaolins initialized\n";
}

HorizonLayer::HorizonLayer(SDL_Renderer* _renderer, int sw, int sh)
{
	renderer = _renderer;
	flipped = false;
	screen_w = sw;
	screen_h = sh;
	
	hObjects[0] = LOAD_BITMAP(renderer, "./Bitmaps/h5big.png");
	hObjects[1] = LOAD_BITMAP(renderer, "./Bitmaps/h4big.png");
	hObjects[2] = LOAD_BITMAP(renderer, "./Bitmaps/h3big.png");
	hObjects[3] = LOAD_BITMAP(renderer, "./Bitmaps/h2big.png");
	hObjects[4] = LOAD_BITMAP(renderer, "./Bitmaps/h1big.png");

	//Sky
	hRects[0].w = 960;	hRects[0].h = 317;	hRects[0].y = 0;
	
	hRects[1].w = 1264;	hRects[1].h = 358;	hRects[1].y = 0;
	hRects[3].w = 1286;	hRects[3].h = 237;	hRects[3].y = screen_h - hRects[3].h;
	hRects[4].w = 1602;	hRects[4].h = 145;	hRects[4].y = screen_h - hRects[4].h;
	hRects[2].w = 1584;	hRects[2].h = 122;	
	hRects[2].y = screen_h - hRects[2].h*1.5;
	hRects[2].x = ((hRects[2].w - screen_w) / 2)*(-1);

	/*srcRect[2].w = screen_w;
	srcRect[2].x = (hRects[2].w - screen_w) / 2;
	dstRect[2].x = 0;
	srcRect[2].h = hRects[2].h;
	dstRect[2].y = hRects[2].y;

	dstRect[2].w = srcRect[2].w;
	dstRect[2].h = srcRect[2].h;*/

	InitializeShaolins(renderer);
}


HorizonLayer::~HorizonLayer()
{
}
