#include "../AnimationFilms/AnimationFilm.h"

class Sprite {
	byte frameNo;
	SDL_Rect frameBox;
	int x, y;
	bool isVisible;
	AnimationFilm* currFilm;
	//TileLayer* myLayer;
	
public:
	void SetFrame(byte i) {
		if (i != frameNo) {
			assert(i < currFilm->GetTotalFrames());

			frameBox = currFilm->GetFrameBox(frameNo = i);
		}
	}
	byte GetFrame(void) const { return frameNo; }
	void SetVisibility(bool v) { isVisible = v; }
	bool IsVisible(void) const { return isVisible; }

	AnimationFilm* GetAnimationFilm() {
		return currFilm;
	}

	bool CollisionCheck(Sprite* s);
	void Display(BITMAP* dest, const SDL_Rect& da, SDL_Renderer *renderer);
	void Move(int dx, int dy);
	void SetAnimFilm(AnimationFilm* _film, bool _reverseAnim = false);

	Sprite(int _x, int _y, AnimationFilm* film) :
		x(_x), y(_y), currFilm(film), isVisible(true)
	{
		frameNo = currFilm->GetTotalFrames(); SetFrame(0);
	}
};