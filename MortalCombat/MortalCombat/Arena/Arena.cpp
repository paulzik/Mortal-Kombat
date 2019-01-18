#include "Arena.h"
#include "../Animator/Sprites/AnimationFilms/AnimationFilmHolder.h"

#include "../Animator/Animator/AnimatorHolder.h"

#include "../InputManager/InputManager.h"
#include "../../Libraries/include/SDL.h"

Arena::Arena(SDL_Renderer *renderer)
{
	//InitializeArena(renderer);
}

//Arena::~Arena()
//{
//}

void Arena::InitializeArena(SDL_Renderer *renderer)
{
	//AnimationFilmHolder& AFH = AnimationFilmHolder::Get();
	//AFH.Load("Arena", renderer);

	//sprite = new Sprite(0, 0, AFH.GetFilm("Sky"));

	//animators = new Animators();
	//animators->insert(std::pair<std::string, Animator*>("Sky", new MovingAnimator()));
}
