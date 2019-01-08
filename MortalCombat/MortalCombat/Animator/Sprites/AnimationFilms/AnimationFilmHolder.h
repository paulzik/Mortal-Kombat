#pragma once
#include "AnimationFilm.h"
#include "BitmapLoader.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <map>

class AnimationFilmHolder {
private:
	typedef std::map<std::string, AnimationFilm*> Films;
	Films films;
	BitmapLoader loader;
	static AnimationFilmHolder holder;
	
	

public:
	static const AnimationFilmHolder& Get(void) {
		return holder;
	}
	AnimationFilmHolder(void) {}
	~AnimationFilmHolder() { CleanUp(); }
	void Load(const std::string& catalogue, SDL_Renderer* rend) {
		std::string path = catalogue;
		for (const auto & entry : std::filesystem::directory_iterator(path)) {
			std::cout << entry.path() << std::endl;
			BITMAP* bm = loader.Load(entry.path().string(), rend);
			const std::string s = "Subzero";
			std::vector<SDL_Rect> rects;
			int width, height;
			SDL_QueryTexture(bm, NULL, NULL, &width, &height);
			int boxe_number = width / 32;
			for (int i = 0; i < boxe_number; i++) {
				int offsetX = 32, offsetY = 71;
				SDL_Rect tmp;
				tmp.x = i * offsetX;
				tmp.y = 0;
				tmp.w = offsetX;
				tmp.h = offsetY;
				rects.push_back(tmp);
			}
			AnimationFilm* anim = new AnimationFilm(bm, rects, s);

			films.insert(std::pair<std::string, AnimationFilm*>(entry.path().string().substr(entry.path().string().find_last_of("/", 100)+1).erase(entry.path().string().substr(entry.path().string().find_last_of("/", 100) + 1).find(".")), anim));
		}
	}

	void CleanUp(void) {
		for (std::pair<std::string, AnimationFilm*> var : films)
		{
			delete (var.second);
		}
		films.clear();
	}

	AnimationFilm* GetFilm(const std::string id) {
		//Films::iterator i = films.find(id);
		//return i != films.end ? i->second : (AnimationFilm*) 0;.


		for (auto entry : films) {
			if (entry.first._Equal(id)) {
				return entry.second;
			}
		}
		return NULL;
	}
};