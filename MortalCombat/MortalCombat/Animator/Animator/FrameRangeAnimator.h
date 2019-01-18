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
	
	void Start(Sprite* s, FrameRangeAnimation* a, timestamp_t t, bool isReverse = false) {
		sprite = s;
		anim = a;
		lastTime = t;
		state = ANIMATOR_RUNNING;
		sprite->SetFrame(currFrame = anim->GetStartFrame());
		sprite->GetAnimationFilm()->SetReverseAnimation(isReverse);
	}

	FrameRangeAnimator* SetType(animatortype_t _animType) {
		type = _animType;
		return this;
	}

	Sprite* GetSprite() {
		return sprite;
	}

	FrameRangeAnimator(int _id) :
		sprite((Sprite*)0),
		anim((FrameRangeAnimation*)0), currFrame(0xFF)
		
	{
		ID = _id;
	}
	~FrameRangeAnimator() {}

	// Inherited via Animator
	virtual void Render(SDL_Renderer* rend) override;
};