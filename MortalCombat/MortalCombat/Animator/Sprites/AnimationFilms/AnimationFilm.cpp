#include "AnimationFilm.h"
#include <iostream>
void AnimationFilm::DisplayFrame(SDL_Texture *dest, const SDL_Rect& at, BYTE frameNo, SDL_Renderer* rend, bool _fliped) const {
	if (id == "Walk") {
		std::cout << id.c_str() << ": " << fliped << std::endl;
	}
	if (fliped) {
		SDL_RendererFlip flip = SDL_FLIP_VERTICAL;

		SDL_RenderCopyEx(rend, dest, &boxes[frameNo], &at, 180, NULL, flip);
	}
	else {
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


}

AnimationFilm::AnimationFilm(SDL_Texture* film, const std::vector<SDL_Rect> rects, const std::string & type, bool _fliped)
{
	bitmap = film;

	for (int i = 0; i < rects.size(); i++) {
		boxes.push_back(rects[i]);
	}

	id = type;

	fliped = _fliped;
}
