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

void AnimationFilmHolder::LoadBattleUIAnimations(SDL_Renderer *rend)
{
	int bmframes[4] = {22,21,2,2};
	std::string bmnames[4] = { "fight","finishhim","scorpionwins","subzerowins" };

	int i, j;
	BITMAP* bm;
	int width, height;

	for(int k = 0; k < 4; ++k)
	{
		bm = loader.Load("./Bitmaps/BattleElements/"+bmnames[k]+".png", rend);
		SDL_QueryTexture(bm, NULL, NULL, &width, &height);
		std::vector<SDL_Rect> rects;
		for (int i = 0; i < bmframes[k]; ++i)
		{
			SDL_Rect box;
			box.x = i*(width/ bmframes[k]);
			box.y = 0;
			box.w = width/ bmframes[k];
			box.h = height;
			rects.push_back(box);
		}
		AnimationFilm* anim = new AnimationFilm(bm, rects, bmnames[k]);
		films.insert(std::pair<std::string, AnimationFilm*>(bmnames[k], anim));
	}
}