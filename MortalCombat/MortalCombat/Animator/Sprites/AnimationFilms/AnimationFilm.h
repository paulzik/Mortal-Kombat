#pragma once

#include <vector>
#include <string> 
#include "../../SDL_Helper.h"
#include <assert.h> 
#include "SDL.h"

typedef unsigned char BYTE;

class AnimationFilm {
private:
	std::vector<SDL_Rect> boxes;
	SDL_Texture* bitmap;
	std::string id;
	bool reverse;
	bool fliped = false;


public:
	BYTE GetTotalFrames(void) const { return boxes.size(); }
	SDL_Texture* GetBitmap(void) const { return bitmap; }
	const std::string GetId(void) const { return id; }

	void SetReverseAnimation(bool rev) {
		reverse = rev;
	}

	void SetFliped(bool _flip) {
		fliped = _flip;
	}

	bool GetIsFliped() {
		return fliped;
	}

	bool GetIsAnimationReversed() {
		return reverse;
	}

	const SDL_Rect GetFrameBox(BYTE frameNo) const
	{
		assert(boxes.size() > frameNo); return boxes[frameNo];
	}
	void DisplayFrame(SDL_Texture *d, const SDL_Rect& at, BYTE frameNo, SDL_Renderer*, bool _fliped) const;

	AnimationFilm(SDL_Texture* dest, const std::vector<SDL_Rect>, const std::string&, bool _fliped = false);
};

