#include "Animation.h"

typedef unsigned char frame_t;

struct PathEntry {
	offset_t dx, dy;
	frame_t frame;
	delay_t delay;

	PathEntry(void) : dx(0), dy(0), frame(0xff), delay(0) {}

	PathEntry(const PathEntry& p) :
		dx(p.dx), dy(p.dy), frame(p.frame), delay(p.delay) {}

};


class MovingPathAnimation : Animation {
private:
	std::list<PathEntry> path;

public:
	const std::list<PathEntry>& GetPath(void) const {
		return path;
	}

	void SetPath(const std::list<PathEntry>& p) {
		path.clear();
		path = p;
	}

	Animation* Clone(animid_t newId) const {
		return new MovingPathAnimation(path, newId);
	}

	MovingPathAnimation(const std::list<PathEntry>& _path, animid_t id) :
		path(_path), Animation(id) {}

};