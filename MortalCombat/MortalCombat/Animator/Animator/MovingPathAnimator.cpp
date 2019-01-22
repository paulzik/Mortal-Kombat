#include "MovingPathAnimator.h"
#include <iostream>
#include <math.h>
bool fall;
bool once;
void MovingPathAnimator::Progress(timestamp_t currTime) {
	if (currTime > lastTime && currTime - lastTime >= anim->GetDelay()) {
		int x = anim->GetDx();

		if (fall) {
			if (sprite->y < 150)
				sprite->y += (float)sqrt((((1 - (sprite->x / 800) ^ 2))) / 10.0f) * 5;
			else if (sprite->y < 200)
				sprite->y += (float)sqrt((((1 - (sprite->x / 800) ^ 2))) / 10.0f) * 15;
			else if (sprite->y < 250)
				sprite->y += (float)sqrt((((1 - (sprite->x / 800) ^ 2))) / 10.0f) * 25;
			else
				sprite->y += (float)sqrt((((1 - (sprite->x / 800) ^ 2))) / 10.0f) * 35;
		}
		else {
			if (sprite->y < 150)
				sprite->y -= (float)sqrt((((1 - (sprite->x / 800) ^ 2))) / 10.0f) * 5;
			else if (sprite->y < 200)
				sprite->y -= (float)sqrt((((1 - (sprite->x / 800) ^ 2))) / 10.0f) * 15;
			else if (sprite->y < 250)
				sprite->y -= (float)sqrt((((1 - (sprite->x / 800) ^ 2))) / 10.0f) * 25;
			else
				sprite->y -= (float)sqrt((((1 - (sprite->x / 800) ^ 2))) / 10.0f) * 35;
		}
		sprite->Move(x, 0);

		if (sprite->y < 100 && !once) {
			once = true;
			fall = true;

		}

		std::cout << sprite->y << std::endl;
		if (sprite->y >= 330) {
			state = ANIMATOR_FINISHED;
			sprite->y = 330;
			NotifyStopped();
			fall = false;
			once = false;
			return;
		}

		//if (!anim->GetCont()) {
		//	state = ANIMATOR_FINISHED;
		//	NotifyStopped();
		//	return;
		//}
		else {
			lastTime += anim->GetDelay();
			//Progress(currTime); // Recursion (make it a loop)
		}
	}
}

void MovingPathAnimator::Render(SDL_Renderer * rend)
{
}

void MovingPathAnimator::SetLogicState(logic::StateTransitions & state)
{
	state.SetState("Idle");
}
