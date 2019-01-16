#include "AnimationFilm.h"

void AnimationFilm::DisplayFrame(SDL_Texture *dest, const SDL_Rect& at, BYTE frameNo, SDL_Renderer* rend) const {
	//MaskedBlit(bitmap, GetFrameBox(frameNo), dest, at);


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
