#pragma once
#include "../../Libraries/include/SDL.h"
#include "../Animator/Animator/MovingAnimator.h"
#include <map>
#include "../Animator/Sprites/AnimationFilms/AnimationFilmHolder.h"
#include "../Animator/Animator/AnimatorHolder.h"
#include "../Animator/Animator/FrameRangeAnimator.h"
#include "../InputManager/InputManager.h"
//#include "../Animator/Sprites/Sprite/Sprite.h"

class Arena
{
public:
	Arena(SDL_Renderer *renderer);
	//~Arena();
private:
	Sprite*	sprite = nullptr;
	typedef std::map<std::string, Animator*> Animators;
	Animators* animators;

	void InitializeArena(SDL_Renderer *renderer);
};

