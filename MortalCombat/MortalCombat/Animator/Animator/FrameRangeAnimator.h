#pragma once
#include "Animator.h"
#include "../Sprites/Sprite/Sprite.h"
#include "../AnimationTypes/FrameRangeAnimation.h"

class FrameRangeAnimator : public Animator {
	Sprite* sprite;
	FrameRangeAnimation* anim;
	frame_t currFrame;

public:
	void Progress(timestamp_t currTime);
	
	void Start(Sprite* s, FrameRangeAnimation* a, timestamp_t t) {
		sprite = s;
		anim = a;
		lastTime = t;
		state = ANIMATOR_RUNNING;
		sprite->SetFrame(currFrame = anim->GetStartFrame());
	}



	FrameRangeAnimator(void) :
		sprite((Sprite*)0),
		anim((FrameRangeAnimation*)0), currFrame(0xFF) {}
	~FrameRangeAnimator() {}

	// Inherited via Animator
	virtual void Render(SDL_Renderer* rend) override;
};