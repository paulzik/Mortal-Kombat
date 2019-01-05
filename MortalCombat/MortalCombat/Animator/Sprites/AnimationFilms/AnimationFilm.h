#pragma once

#include <vector>
#include "../../SDL_Helper.h"
#include <assert.h> 
#include "SDL.h"

typedef unsigned char byte;

class AnimationFilm {
private:
	std::vector<SDL_Rect> boxes;
	SDL_Texture* bitmap;
	std::string id;

public:
	byte GetTotalFrames(void) const { return boxes.size(); }
	SDL_Texture* GetBitmap(void) const { return bitmap; }
	const std::string GetId(void) const { return id; }
	const SDL_Rect GetFrameBox(byte frameNo) const
	{
		assert(boxes.size() > frameNo); return boxes[frameNo];
	}
	void DisplayFrame(SDL_Texture *d, const SDL_Rect& at, byte frameNo, SDL_Renderer*) const;

	AnimationFilm(SDL_Texture* dest, const std::vector<SDL_Rect>, const std::string&);
};

