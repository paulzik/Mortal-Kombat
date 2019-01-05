#include "MovingAnimation.h"

typedef unsigned char frame_t;

class FrameListAnimation : MovingAnimation {
private:
	std::list<frame_t> frames;

public:
	const std::list<frame_t>& GetFrames(void) const {
		return frames;
	}

	void SetFrames(const std::list<frame_t> & f) {
		frames.clear();
		frames = f;
	}

	Animation* Clone(animid_t newId) const {
		return new FrameListAnimation(frames, GetDx(), GetDy(), GetDelay(), GetContinuous(), newId);
	}

	FrameListAnimation(const std::list<frame_t>& _frames, offset_t dx, offset_t dy, delay_t d, bool c, animid_t id) :
		frames(_frames), MovingAnimation(dx, dy, d, c, id) {}
};