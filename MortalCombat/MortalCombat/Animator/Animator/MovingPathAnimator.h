#pragma once
#include "Animator.h"
#include "../AnimationTypes/MovingPathAnimation.h"
#include "../Sprites/Sprite/Sprite.h"

class MovingPathAnimator : public Animator {
	Sprite* sprite;
	MovingPathAnimation* anim;

public:
	void Progress(timestamp_t currTime) override;

	void Start(Sprite* s, MovingPathAnimation* a, timestamp_t t) {
		sprite = s;
		anim = a;
		lastTime = t;
		state = ANIMATOR_RUNNING;
	}

	// Inherited via Animator
	virtual void Render(SDL_Renderer* rend) override;

	MovingPathAnimator(int _id) :
		sprite((Sprite*)0), anim((MovingPathAnimation*)0)
	{
		ID = _id;
	}
	~MovingPathAnimator() {}

	// Inherited via Animator
	virtual void SetLogicState(logic::StateTransitions & state) override;
};