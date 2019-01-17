#include "Animator.h"
#include "../AnimationTypes/MovingAnimation.h"
#include "../Sprites/Sprite/Sprite.h"

class MovingAnimator : public Animator {
	Sprite* sprite;
	MovingAnimation* anim;

public:
	void Progress(timestamp_t currTime);
	
	void Start(Sprite* s, MovingAnimation* a, timestamp_t t) {
		sprite = s;
		anim = a;
		lastTime = t;
		state = ANIMATOR_RUNNING;
	}

	// Inherited via Animator
	virtual void Render(SDL_Renderer* rend) override;

	MovingAnimator(void) :
		sprite((Sprite*)0), anim((MovingAnimation*)0) {}
	~MovingAnimator() {}
};