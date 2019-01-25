#include "FrameRangeAnimator.h"
#include "../Animator/AnimatorHolder.h"

void FrameRangeAnimator::Progress(timestamp_t currTime)
{
	while (currTime > lastTime && currTime - lastTime >= anim->GetDelay() && state == ANIMATOR_RUNNING) {
		if (currTime - lastTime > anim->GetDelay() * 2.f) {// failsafe if time difference it too high
			lastTime = currTime;
			if (!sprite->GetAnimationFilm()->GetIsAnimationReversed())
				currFrame = -1;
			else
				currFrame = anim->GetEndFrame() + 1;

		}

		if (currFrame + 1 == anim->GetEndFrame() && anim->HoldLastFrame) {
			state = ANIMATOR_STOPPED;
			return;
		}

		if (!sprite->GetAnimationFilm()->GetIsAnimationReversed())
		{
			if (currFrame == anim->GetEndFrame())
				currFrame = anim->GetStartFrame();
			else
				++currFrame;
		}
		else {
			if (currFrame == anim->GetStartFrame())
				currFrame = anim->GetEndFrame();
			else
				--currFrame;
		}

		sprite->Move(anim->GetDx(), anim->GetDy());
		sprite->SetFrame(currFrame);
		lastTime += anim->GetDelay();

		

		if (currFrame == anim->GetEndFrame() && !anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			//currFrame = anim->GetStartFrame();
			return;
		}
	}
}

void FrameRangeAnimator::SetLogicState(logic::StateTransitions & state)
{
	State = &state;
}

void FrameRangeAnimator::Render(SDL_Renderer* rend)
{
	SDL_Rect srcrect;

	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 90;
	srcrect.h = 140;
	if ((AnimatorHolder::clap == false) && (this->GetID() == 1003))
		return;
	else if ((AnimatorHolder::clap == true) && this->GetID() == 1002)
		return;
	sprite->Display(NULL, srcrect, rend);
}
