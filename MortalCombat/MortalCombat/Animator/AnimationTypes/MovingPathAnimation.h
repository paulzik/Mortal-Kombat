#pragma once
#include "Animation.h"

//typedef unsigned char frame_t;
//
//struct PathEntry {
//	offset_t dx, dy;
//	frame_t frame;
//	delay_t delay;
//
//	PathEntry(void) : dx(0), dy(0), frame(0xff), delay(0) {}
//
//	PathEntry(const PathEntry& p) :
//		dx(p.dx), dy(p.dy), frame(p.frame), delay(p.delay) {}
//
//};
//
//
//class MovingPathAnimation : Animation {
//private:
//	std::list<PathEntry> path;
//
//public:
//	const std::list<PathEntry>& GetPath(void) const {
//		return path;
//	}
//
//	void SetPath(const std::list<PathEntry>& p) {
//		path.clear();
//		path = p;
//	}
//
//	Animation* Clone(animid_t newId) const {
//		return new MovingPathAnimation(path, newId);
//	}
//
//	MovingPathAnimation(const std::list<PathEntry>& _path, animid_t id) :
//		path(_path), Animation(id) {}
//
//};

class MovingPathAnimation : public Animation {
private:
	offset_t x, y;
	double delay;
	bool cont;

public:
	MovingPathAnimation(offset_t dx, offset_t dy, delay_t d, bool c, animid_t id) : Animation(id)
	{
		x = dx;
		y = dy;
		delay = d;
		cont = c;

	}

	offset_t GetDx() {
		return x;
	}

	offset_t GetDy() {
		return y;
	}

	double GetDelay() {
		return delay;
	}

	bool GetCont() {
		return cont;
	}


	// Inherited via Animation
	virtual Animation * Clone(animid_t newId) const override;

};