#include "FrameRangeAnimator.h"

void FrameRangeAnimator::Progress(timestamp_t currTime)
{
	while (currTime > lastTime && currTime - lastTime >= anim->GetDelay() && state == ANIMATOR_RUNNING) {
		if (currFrame == anim->GetEndFrame())
			currFrame = anim->GetStartFrame();
		else
			++currFrame;

		sprite->Move(anim->GetDx(), anim->GetDy());
		sprite->SetFrame(currFrame);
		lastTime += anim->GetDelay();
		if (currFrame == anim->GetEndFrame() && !anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
		}
	}
}

void FrameRangeAnimator::Render(SDL_Renderer* rend)
{
	SDL_Rect srcrect;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 90;
	srcrect.h = 140;
	sprite->Display(NULL, srcrect, rend);
}
