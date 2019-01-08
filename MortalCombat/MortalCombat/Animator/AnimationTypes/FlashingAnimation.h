#include "Animation.h"

typedef unsigned char frame_t;

class FlashingAnimation : Animation {
private:
	frame_t repetitions;
	delay_t hideDelay;
	delay_t showDelay;

public:
	frame_t SetRepetitions(frame_t n) {
		repetitions = n;
	}

	frame_t GetRepetitions(void) const {
		return repetitions;
	}

	void SetHideDelay(delay_t d) {
		hideDelay = d;
	}

	delay_t GetHideDelay(void) const {
		return hideDelay;
	}

	void SetShowDelay(delay_t d) {
		showDelay = d;
	}

	delay_t GetShowDelay(void) const {
		return showDelay;
	}

	Animation* Clone(animid_t newId) const {
		return new FlashingAnimation(repetitions, hideDelay, showDelay, newId);
	}
	
	FlashingAnimation(frame_t n, delay_t show, delay_t hide, animid_t id) :
		repetitions(n), hideDelay(hide), showDelay(show), Animation(id) {}

};