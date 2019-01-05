#include <map>
#include "../../SDL_Helper.h"
#include <assert.h>


class BitmapLoader {
private :
	typedef std::map<std::string, BITMAP*> Bitmaps;
	Bitmaps bitmaps;
	BITMAP* GetBitmap(const std::string path) const {
		Bitmaps::const_iterator i = bitmaps.find(path);
		return i != bitmaps.end() ? i->second : (BITMAP*) 0;
	}

public :
	BITMAP* Load(const std::string& path, SDL_Renderer* rend) {
		BITMAP* b = GetBitmap(path);
		if (!b) {
			bitmaps[path] = { b = LOAD_BITMAP(rend, path.c_str()) };
			assert(b);
		}
		return b;
	}

	void CleanUp(void) {
		for (Bitmaps::iterator i = bitmaps.begin(); i != bitmaps.end(); ++i) {
			//TODO: Destroy Bitmap
		}
		bitmaps.clear();
	}

	BitmapLoader(void) {}
	~BitmapLoader() { CleanUp(); }
};