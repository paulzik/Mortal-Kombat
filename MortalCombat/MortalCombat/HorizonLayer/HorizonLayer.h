#pragma once
#include <queue>

#include "../Animator/SDL_Helper.h"
#include "../Animator/Sprites/AnimationFilms/AnimationFilmHolder.h"
#include "../Animator/Animator/AnimatorHolder.h"
#include "../Animator/Sprites/Sprite/SpritesHolder.h"
#define TOTAL_HOBJECTS	5


class HorizonLayer
{
public:

	HorizonLayer(SDL_Renderer* _renderer, int sw, int sh);
	~HorizonLayer();
private:
	SDL_Renderer	*renderer;
	BITMAP		*hObjects[TOTAL_HOBJECTS];
	SDL_Rect	hRects[TOTAL_HOBJECTS];

	AnimationFilmHolder*	afh;
	AnimatorHolder*		ah;
	typedef std::map<std::string, Animator*>	Animators;
	Animators *animators;
	SpritesHolder* sprites;

	std::queue<Animator*> RunningQueue;
	Animator* currAnimator;

	int screen_w;
	int screen_h;
	bool flipped;

	bool ClippedEntirely(SDL_Rect& area, SDL_Rect& in, SDL_Rect* out);
	void InitializeHorizon(SDL_Renderer *renderer);
};

