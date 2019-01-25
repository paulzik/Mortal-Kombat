#include "Sprite.h"

float Scale = 2.5f;

void Sprite::Display(BITMAP * dest, const SDL_Rect& da, SDL_Renderer *rend)
{
	//SDL_RenderCopy(rend, dest, &frameBox, &da);
	
	SDL_Rect pos;

	if (	currFilm->GetId() == "h0" || currFilm->GetId() == "h1" || currFilm->GetId() == "h2" ||
		currFilm->GetId() == "h3" || currFilm->GetId() == "h4" || currFilm->GetId() == "h5")
	{
		SDL_Rect fb;
		fb = currFilm->GetFrameBox(frameNo);
		pos.w = fb.w;
		pos.h = fb.h;

		pos.x = x;
		pos.y = y;
	}else if (currFilm->GetId() == "scorpionwins" || currFilm->GetId() == "subzerowins"){
		SDL_Rect fb;
		fb = currFilm->GetFrameBox(frameNo);
		pos.w = fb.w * 1.7f;
		pos.h = fb.h * 1.7f;

		pos.x = x;
		pos.y = y;
	}
	else if (currFilm->GetId() == "fight") {
		SDL_Rect fb;
		fb = currFilm->GetFrameBox(frameNo);
		pos.w = fb.w * 2.0f;
		pos.h = fb.h * 2.0f;

		pos.x = x - 85;
		pos.y = y;
	}
	else
	{
		pos.x = x;
		pos.y = y - 89 *Scale;
		pos.w = 89 * Scale;
		pos.h = 149 * Scale;
	}
	if (isVisible)
		currFilm->DisplayFrame(currFilm->GetBitmap(), pos, frameNo, rend, fliped);

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
	x += dx * Scale;
	y += dy * Scale;
}

void Sprite::SetAnimFilm(AnimationFilm * _film, bool _reverseAnim)
{
	currFilm = _film;
	currFilm->SetReverseAnimation(_reverseAnim);
	//frameNo = 0;
}
