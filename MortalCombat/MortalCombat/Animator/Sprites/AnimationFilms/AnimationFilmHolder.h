#pragma once
#include "AnimationFilm.h"
#include "BitmapLoader.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <map>
#include "../../../Configuration/JSONParser/json/json.h"
#include <iostream>
#include <fstream>

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
		std::string path = catalogue + ".png";
		int offsetX = 89, offsetY = 149;

		Json::Value jsonValue;
		std::ifstream file;
		file.open(catalogue + ".json");
		file >> jsonValue;
		file.close();

		for (Json::ValueIterator i = jsonValue.begin(); i != jsonValue.end(); ++i) {
			std::cout << i.name() << std::endl;
			int Array[3];

			BITMAP* bm = loader.Load(path, rend);
			const std::string s = i.name();
			std::vector<SDL_Rect> rects;
			int width, height;
			SDL_QueryTexture(bm, NULL, NULL, &width, &height);

			int count = 0;
			Json::Value tmp = *i;
			for (Json::ValueIterator j = tmp.begin(); j != tmp.end(); ++j) {
				Json::Value temp = *j;
				std::cout << "\t" << j.name() << ": " << temp.asInt() << std::endl;

				Array[count++] = temp.asInt();
			}

			for (int k = 0; k < Array[0]; k++) {
				SDL_Rect box;
				box.x = k * Array[1];
				box.y = Array[2];
				box.w = offsetX;
				box.h = offsetY;
				rects.push_back(box);
			}

		
		//for (const auto & entry : std::filesystem::directory_iterator(path)) {
		//	std::cout << entry.path() << std::endl;
		//	BITMAP* bm = loader.Load(entry.path().string(), rend);
		//	const std::string s = "Subzero";
		//	std::vector<SDL_Rect> rects;
		//	int width, height;
		//	SDL_QueryTexture(bm, NULL, NULL, &width, &height);
		//	int boxe_number = width / 89;
		//	for (int i = 0; i < boxe_number; i++) {
		//		SDL_Rect tmp;
		//		tmp.x = i * offsetX;
		//		tmp.y = 0;
		//		tmp.w = offsetX;
		//		tmp.h = offsetY;
		//		rects.push_back(tmp);
		//	}
			AnimationFilm* anim = new AnimationFilm(bm, rects, s);

			films.insert(std::pair<std::string, AnimationFilm*>(s, anim));
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