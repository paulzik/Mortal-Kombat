#pragma once
#include "Animator/SDL_Helper.h"
#define TOTAL_HOBJECTS	5


class HorizonLayer
{
public:

	void DisplayHorizon(SDL_Rect& vw, SDL_Rect& da);
	HorizonLayer(SDL_Renderer* _renderer);
	~HorizonLayer();
private:
	BITMAP		*hObjects[TOTAL_HOBJECTS];
	SDL_Rect	hRects[TOTAL_HOBJECTS];
	SDL_Renderer	*renderer;

	bool ClippedEntirely(SDL_Rect& area, SDL_Rect& in, SDL_Rect* out);
};

