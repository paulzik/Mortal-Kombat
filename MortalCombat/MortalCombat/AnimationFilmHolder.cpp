#include "Animator/Sprites/AnimationFilms/AnimationFilmHolder.h"

void AnimationFilmHolder::LoadShaolins(SDL_Renderer *rend)
{
	BITMAP* bm;
	int width, height;
	std::vector<SDL_Rect> rects;

	const std::string s = "h3big";
	bm = loader.Load("./Bitmaps/h3big.png", rend);
	SDL_QueryTexture(bm, NULL, NULL, &width, &height);
	for (int i = 0; i < 3; ++i)
	{
		SDL_Rect box;
		box.x = 0;
		box.y = i*122;
		box.w = width;
		box.h = height/3;
		rects.push_back(box);
	}
	AnimationFilm* anim = new AnimationFilm(bm, rects, s);
	films.insert(std::pair<std::string, AnimationFilm*>(s, anim));
}