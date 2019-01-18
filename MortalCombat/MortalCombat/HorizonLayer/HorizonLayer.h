#pragma once
#include "../Animator/SDL_Helper.h"
#define TOTAL_HOBJECTS	5


class HorizonLayer
{
public:

	void DisplayHorizon();
	HorizonLayer(SDL_Renderer* _renderer, int sw, int sh);
	~HorizonLayer();
private:
	BITMAP		*hObjects[TOTAL_HOBJECTS];
	SDL_Rect	hRects[TOTAL_HOBJECTS];
	SDL_Renderer	*renderer;
	SDL_Rect dstRect[5];
	SDL_Rect srcRect[5];
	//SDL_Rect	dstRect;
	

	int screen_w;
	int screen_h;

	bool ClippedEntirely(SDL_Rect& area, SDL_Rect& in, SDL_Rect* out);
};

