#pragma once
#include "../AnimationFilms/AnimationFilm.h"

class Sprite {
	BYTE frameNo;
	SDL_Rect frameBox;
	bool isVisible;
	AnimationFilm* currFilm;
	bool fliped = false;
	//TileLayer* myLayer;
	
public:
	int &x, &y;

	void SetFrame(BYTE i) {
		if (i != frameNo) {
			if (i >= currFilm->GetTotalFrames()) i = currFilm->GetTotalFrames()-1;
			assert(i < currFilm->GetTotalFrames());

			frameBox = currFilm->GetFrameBox(frameNo = i);
		}
	}
	BYTE GetFrame(void) const { return frameNo; }
	void SetVisibility(bool v) { isVisible = v; }
	bool IsVisible(void) const { return isVisible; }

	AnimationFilm* GetAnimationFilm() {
		return currFilm;
	}

	bool CollisionCheck(Sprite* s);
	void Display(BITMAP* dest, const SDL_Rect& da, SDL_Renderer *renderer);
	void Move(int dx, int dy);
	void SetAnimFilm(AnimationFilm* _film, bool _reverseAnim = false);

	void SetFlipped(bool _flip) {
		fliped = _flip;
	}


	Sprite(int& _x, int& _y, AnimationFilm* film, bool& _fliped) :
		x(_x), y(_y), currFilm(film), isVisible(true), fliped(_fliped)
	{
		frameNo = currFilm->GetTotalFrames(); SetFrame(0);
		currFilm->SetFliped(_fliped);
	}
};