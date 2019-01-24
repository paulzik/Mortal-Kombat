#include "AnimationFilm.h"
#include <iostream>
void AnimationFilm::DisplayFrame(SDL_Texture *dest, const SDL_Rect& at, BYTE frameNo, SDL_Renderer* rend, bool _fliped) const {

	if (id == "Walk") {
		std::cout << id.c_str() << ": " << fliped << std::endl;
	}
	if (_fliped) {
		SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
		SDL_Rect rect;
		rect = at;
		if (id == "Rope" || id == "Burn" || id == "Freezeball") {
			rect.w = boxes[frameNo].w * 2.5f;
		}
		rect.x += 89;
		SDL_Point point;
		point.x = 0;
		point.y = boxes[frameNo].h + 37; // for some reason 37 :|

		SDL_RenderCopyEx(rend, dest, &boxes[frameNo], &rect, 180, &point, flip);
	}
	else {
		SDL_Rect rect;
		rect = at;
		if (id == "Rope" || id == "Burn") {
			rect.w = boxes[frameNo].w * 2.5f;
		}
		SDL_RenderCopy(rend, dest, &boxes[frameNo], &rect);
	}


}

AnimationFilm::AnimationFilm(SDL_Texture* film, const std::vector<SDL_Rect> rects, const std::string & type, bool _fliped)
{
	bitmap = film;

	for (int i = 0; i < rects.size(); i++) {
		boxes.push_back(rects[i]);
	}

	id = type;

	//fliped = _fliped;
}
