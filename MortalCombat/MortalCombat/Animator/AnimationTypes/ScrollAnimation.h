#include "Animation.h"

typedef unsigned char HorizScroll;
typedef unsigned char VertScroll;


struct ScrollEntry
{
	HorizScroll h;
	VertScroll v;
	delay_t delay;
};

class ScrollAnimation : Animation {
private:
	std::list<ScrollEntry> scroll;

public:
	const std::list<ScrollEntry>& GetScroll(void) const {
		return scroll;
	}

	void SetScroll(const std::list<ScrollEntry>& p) {
		scroll.clear();
		scroll = p;
	}

	Animation* Clone(animid_t newId) const {
		return new ScrollAnimation(scroll, newId);
	}

	ScrollAnimation(const std::list<ScrollEntry>& _scroll, animid_t id) :
		scroll(_scroll), Animation(id) {}

};