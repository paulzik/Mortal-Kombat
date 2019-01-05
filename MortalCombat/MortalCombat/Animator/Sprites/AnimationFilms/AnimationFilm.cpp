#include "AnimationFilm.h"

void AnimationFilm::DisplayFrame(SDL_Texture *dest, const SDL_Rect& at, byte frameNo, SDL_Renderer* rend) const {
	//MaskedBlit(bitmap, GetFrameBox(frameNo), dest, at);
	SDL_Rect a;
	a.x = 0;
	a.y = 0;
	a.w = 32*2;
	a.h = 71*2;
	SDL_RenderCopy(rend, dest, &boxes[frameNo], &at);
}

AnimationFilm::AnimationFilm(SDL_Texture* film, const std::vector<SDL_Rect> rects, const std::string & type)
{
	bitmap = film;

	for (int i = 0; i < rects.size(); i++) {
		boxes.push_back(rects[i]);
	}

	id = type;
}
