#include "MovingAnimator.h"
#include <iostream>
bool stop = false;
void MovingAnimator::Progress(timestamp_t currTime)
{
	if (currTime > lastTime && currTime - lastTime >= anim->GetDelay()) {
		int x = anim->GetDx();
		int y = anim->GetDy();
		if (sprite->y < 150) {
			stop = true;
		}

		sprite->Move(x, y);

		
		if (!anim->GetContinuous() && stop) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
		}
		else {
			lastTime += anim->GetDelay();
			//Progress(currTime); // Recursion (make it a loop)
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
	//sprite->Display(NULL, srcrect, rend);
}

void MovingAnimator::SetLogicState(logic::StateTransitions & state)
{
	State = &state;
}
