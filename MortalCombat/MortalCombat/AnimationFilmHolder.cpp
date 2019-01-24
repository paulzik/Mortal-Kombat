#include "Animator/Sprites/AnimationFilms/AnimationFilmHolder.h"
#include <string>

void AnimationFilmHolder::LoadHorizon(SDL_Renderer *rend)
{
	int i,j;
	BITMAP* bm;
	int width, height;

	for (int i = 0; i < 5; ++i)
	{
		std::vector<SDL_Rect> rects;
		bm = loader.Load("./Bitmaps/Horizon/h" + std::to_string(i) + ".png", rend);
		SDL_QueryTexture(bm, NULL, NULL, &width, &height);
		if (i != 2)
		{
			SDL_Rect box;
			box.x = 0;
			box.y = 0;
			box.w = width;
			box.h = height;
			rects.push_back(box);
		}
		else
		{
			for (int j = 0; j < 3; ++j)
			{
				SDL_Rect box;
				box.x = 0;
				box.y = j * (height / 3);
				box.w = width;
				box.h = height / 3;
				rects.push_back(box);
			}
		}
		AnimationFilm* anim = new AnimationFilm(bm, rects, "h" + std::to_string(i));
		films.insert(std::pair<std::string, AnimationFilm*>("h" + std::to_string(i), anim));
	}
}