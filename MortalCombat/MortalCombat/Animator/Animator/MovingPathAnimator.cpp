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
				sprite->y += (float)sqrt((((1 - pow((sprite->x / 800), 2)))) / 10.0f) * 10;
			else if (sprite->y < 200)
				sprite->y += (float)sqrt((((1 - pow((sprite->x / 800), 2)))) / 10.0f) * 20;
			else if (sprite->y < 250)
				sprite->y += (float)sqrt((((1 - pow((sprite->x / 800), 2)))) / 10.0f) * 30;
			else
				sprite->y += (float)sqrt((((1 - pow((sprite->x / 800), 2)))) / 10.0f) * 40;
		}
		else {
			if (sprite->y < 150)
				sprite->y -= (float)sqrt((((1 - pow((sprite->x / 800), 2)))) / 10.0f) * 10;
			else if (sprite->y < 200)
				sprite->y -= (float)sqrt((((1 - pow((sprite->x / 800), 2)))) / 10.0f) * 20;
			else if (sprite->y < 250)
				sprite->y -= (float)sqrt((((1 - pow((sprite->x / 800), 2)))) / 10.0f) * 30;
			else
				sprite->y -= (float)sqrt((((1 - pow((sprite->x / 800), 2)))) / 10.0f) * 40;
		}
		sprite->Move(x, 0);

		if (sprite->y < 100 && !once) {
			once = true;
			fall = true;

		}

		if (sprite->y >= 330) {
			state = ANIMATOR_FINISHED;
			sprite->y = 330;
			NotifyStopped();
			fall = false;
			once = false;
			return;
		}

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
