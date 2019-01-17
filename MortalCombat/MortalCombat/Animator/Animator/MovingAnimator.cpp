#include "MovingAnimator.h"

void MovingAnimator::Progress(timestamp_t currTime)
{
	if (currTime > lastTime && currTime - lastTime >= anim->GetDelay()) {
		sprite->Move(anim->GetDx(), anim->GetDy());
		if (!anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
		}
		else {
			lastTime += anim->GetDelay();
			Progress(currTime); // Recursion (make it a loop)
		}
	}
}

void MovingAnimator::Render(SDL_Renderer* rend)
{
	SDL_Rect srcrect;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = sprite->GetFrame();
	srcrect.h = 140;
	sprite->Display(NULL, srcrect, rend);
}
