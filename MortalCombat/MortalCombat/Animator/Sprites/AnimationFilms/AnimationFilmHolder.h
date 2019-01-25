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

	void LoadHorizon(SDL_Renderer* rend);
	void LoadBattleUIAnimations(SDL_Renderer* rend);

public:
	static AnimationFilmHolder& Get(void) {
	static AnimationFilmHolder holder;
		return holder;
	}
	AnimationFilmHolder(void) {}
	~AnimationFilmHolder() { CleanUp(); }
	void Load(const std::string& catalogue, SDL_Renderer* rend) {

		if (catalogue == "Horizon")
		{
			LoadHorizon(rend);
			return;
		}

		if (catalogue == "BattleUI")
		{
			LoadBattleUIAnimations(rend);
			return;
		}

		std::string path = catalogue + ".png";
		int offsetX = 89, offsetY = 149;

		Json::Value jsonValue;
		std::ifstream file;
		file.open(catalogue + ".json");
		file >> jsonValue;
		file.close();

		for (Json::ValueIterator i = jsonValue.begin(); i != jsonValue.end(); ++i) {
			//std::cout << i.name() << std::endl;
			if (i.name() == "Getoverhere") continue;
			//if (i.name() == "Rope") continue;
			//if (i.name() == "Burn") continue;
			//if (i.name() == "Freezeball") continue;
			int Array[50];

			BITMAP* bm = loader.Load(path, rend);
			const std::string s = i.name();
			std::vector<SDL_Rect> rects;
			int width, height;
			SDL_QueryTexture(bm, NULL, NULL, &width, &height);

			int count = 0;
			Json::Value tmp = *i;
			for (Json::ValueIterator j = tmp.begin(); j != tmp.end(); ++j) {
				Json::Value temp = *j;


				Array[count++] = temp.asInt();
			}

			for (int k = 0; k < tmp["frames"].asInt(); k++) {
				if (i.name() == "Rope"){
					SDL_Rect box;
					box.x = jsonValue["Rope"]["xoffset"].asInt();
					box.w = offsetX;
					box.y = jsonValue["Rope"]["yoffset"].asInt();
					box.h = offsetY;
					rects.push_back(box);

					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 1;
					box.w = offsetX ;
					rects.push_back(box);
					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 2;
					box.w = offsetX ;
					rects.push_back(box);
					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 3;
					box.w = offsetX;
					rects.push_back(box);

					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 4;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 6;
					box.w = offsetX * 2;
					rects.push_back(box);

					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 8;
					box.w = offsetX * 3;
					rects.push_back(box);
					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 11;
					box.w = offsetX * 3;
					rects.push_back(box);

					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 14;
					box.w = offsetX * 4;
					rects.push_back(box);
					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 18;
					box.w = offsetX * 4;
					rects.push_back(box);

					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 22;
					box.w = offsetX * 5;
					rects.push_back(box);

					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 27;
					box.w = offsetX * 1;
					rects.push_back(box);
					box.x = jsonValue["Rope"]["xoffset"].asInt() + offsetX * 27;
					box.w = offsetX * 1;
					rects.push_back(box);

					break;
				}
				else if (i.name() == "Burn") {
					SDL_Rect box;
					box.x = jsonValue["Burn"]["xoffset"].asInt();
					box.w = offsetX;
					box.y = jsonValue["Burn"]["yoffset"].asInt();
					box.h = offsetY;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 1;
					box.w = offsetX;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 2;
					box.w = offsetX;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 3;
					box.w = offsetX;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 4;
					box.w = offsetX;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 5;
					box.w = offsetX;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 6;
					box.w = offsetX;
					rects.push_back(box);

					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 7;
					box.w = offsetX;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 9;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 11;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 13;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 15;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 17;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 19;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 21;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 23;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 25;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 27;
					box.w = offsetX * 2;
					rects.push_back(box);

					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 29;
					box.w = offsetX;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 30;
					box.w = offsetX;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 30;
					box.w = offsetX;
					rects.push_back(box);
					box.x = jsonValue["Burn"]["xoffset"].asInt() + offsetX * 30;
					box.w = offsetX;
					rects.push_back(box);

					break;
				}
				else if (i.name() == "Freezeball") {
					SDL_Rect box;
					box.x = jsonValue["Freezeball"]["xoffset"].asInt();
					box.w = offsetX;
					box.y = jsonValue["Freezeball"]["yoffset"].asInt();
					box.h = offsetY;
					rects.push_back(box);
					box.x = jsonValue["Freezeball"]["xoffset"].asInt() + offsetX * 1;
					box.w = offsetX;
					rects.push_back(box);
					box.x = jsonValue["Freezeball"]["xoffset"].asInt() + offsetX * 2;
					box.w = offsetX;
					rects.push_back(box);
					box.x = jsonValue["Freezeball"]["xoffset"].asInt() + offsetX * 3;
					box.w = offsetX;
					rects.push_back(box);

					box.x = jsonValue["Freezeball"]["xoffset"].asInt() + offsetX * 4;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Freezeball"]["xoffset"].asInt() + offsetX * 6;
					box.w = offsetX * 2;
					rects.push_back(box);
					box.x = jsonValue["Freezeball"]["xoffset"].asInt() + offsetX * 8;
					box.w = offsetX * 2;
					rects.push_back(box);

					box.x = jsonValue["Freezeball"]["xoffset"].asInt() + offsetX * 10;
					box.w = offsetX * 3;
					rects.push_back(box);
					box.x = jsonValue["Freezeball"]["xoffset"].asInt() + offsetX * 13;
					box.w = offsetX * 3;
					rects.push_back(box);

					box.x = jsonValue["Freezeball"]["xoffset"].asInt() + offsetX * 16;
					box.w = offsetX * 4;
					rects.push_back(box);
					box.x = jsonValue["Freezeball"]["xoffset"].asInt() + offsetX * 20;
					box.w = offsetX * 4;
					rects.push_back(box);

					box.x = jsonValue["Freezeball"]["xoffset"].asInt() + offsetX * 24;
					box.w = offsetX * 1;
					rects.push_back(box);
				}
				else {
					SDL_Rect box;
					box.x = (k)*offsetX + Array[1];
					box.y = Array[2];
					box.w = offsetX;
					box.h = offsetY;
					rects.push_back(box);
				}
				

			}
			SDL_Rect box;
			box.x = (tmp["frames"].asInt() - 1)*offsetX + Array[1];
			box.y = Array[2];
			box.w = offsetX;
			box.h = offsetY;
			rects.push_back(box);
		
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

	void FlipFilms(bool _flip) {
		for (auto film : films) {
			film.second->SetFliped(_flip);
		}
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