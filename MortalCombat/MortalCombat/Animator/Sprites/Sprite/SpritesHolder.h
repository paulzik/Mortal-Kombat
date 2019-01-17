#pragma once
#include <list>
#include <map>
#include "Sprite.h"

class SpritesHolder {
private:
	static SpritesHolder holder;
public:
	typedef std::list<Sprite*> SpriteList;

protected:
	typedef std::map<unsigned, SpriteList> SpritesByType;
	SpritesByType sprites;

public:
	void Add(Sprite* s, unsigned _type) {
		sprites[_type].push_back(s);
	}

	void Remove(Sprite* s, unsigned _type) {
		sprites[_type].remove(s);
	}

	void GetSprites(unsigned type, SpriteList* result) const {
		SpritesByType::const_iterator i = sprites.find(type);
		if (i != sprites.end()) {
			*result = i->second;
		}
	}

	static SpritesHolder& Get(void) {
		return holder;
	}
};