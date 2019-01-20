#include "AnimationFilm.h"

void AnimationFilm::DisplayFrame(SDL_Texture *dest, const SDL_Rect& at, BYTE frameNo, SDL_Renderer* rend) const {
	//MaskedBlit(bitmap, GetFrameBox(frameNo), dest, at);

	//if (frameNo >= boxes.size()) frameNo = boxes.size() - 1;
	SDL_RendererFlip flip = SDL_FLIP_VERTICAL;

	//SDL_Point point;
	//point.x = at.x;
	//point.y = at.y * 1.65f;

	//SDL_RenderCopyEx(rend, dest, &boxes[frameNo], &at, 180, &point, flip);
	SDL_Rect rect;
	rect = at;
	if (id == "Rope") {
		rect.x = 120 + at.x;
		rect.y = at.y - 150;
		rect.w = at.w;
		rect.h = at.h;
	}
	SDL_RenderCopy(rend, dest, &boxes[frameNo], &rect);

}

AnimationFilm::AnimationFilm(SDL_Texture* film, const std::vector<SDL_Rect> rects, const std::string & type)
{
	bitmap = film;

	for (int i = 0; i < rects.size(); i++) {
		boxes.push_back(rects[i]);
	}

	id = type;
}
