#include "Sprite.h"

void Sprite::Display(BITMAP * dest, const SDL_Rect& da, SDL_Renderer *rend)
{
	//SDL_RenderCopy(rend, dest, &frameBox, &da);
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos.w = 89;
	pos.h = 149;
	currFilm->DisplayFrame(currFilm->GetBitmap(), pos, frameNo, rend);

	//SDL_Rect visibleArea;
	//SDL_Rect spriteArea;
	//spriteArea.x = da.x;
	//spriteArea.y = da.y;
	//spriteArea.w = da.x;
	//spriteArea.h = da.x;

	//(da.x, da.y, frameBox.w, frameBox.h);
	//if (!ClippedEntirely(spriteArea, myLayer->GetPixelViewWindow(), &visibleArea)) {
	//	SDL_Rect clippedFrame;
	//	clippedFrame.x = frameBox.x + (visibleArea.x - x);
	//	clippedFrame.y = frameBox.y + (visibleArea.y - y);
	//	clippedFrame.w = visibleArea.w;
	//	clippedFrame.h = visibleArea.h;
	//	
	//	//Point at(
	//	//	da.x + (visibleArea.x - myLayer->GetViewWinX()),
	//	//	da.y + (visibleArea.y - myLayer->GetViewWinY())
	//	//);
	//	/*MaskedBlit(
	//		currFilm->GetBitmap(), clippedFrame,
	//		dest, at
	//	);*/
	//}
	//TODO: Display Sprite
}

void Sprite::Move(int dx, int dy)
{
	//TODO: Make Sprite Movement
	x += dx;
	y += dy;
}

void Sprite::SetAnimFilm(AnimationFilm * _film, bool _reverseAnim)
{
	currFilm = _film;
	currFilm->SetReverseAnimation(_reverseAnim);
	//frameNo = 0;
}
