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

	//void LoadArena(SDL_Renderer* rend)
	//{
	//	int Array[4];
	//	int count;
	//	Json::Value jsonValue;
	//	std::ifstream file;
	//	BITMAP* bm = loader.Load("./Bitmaps/Arena.png", rend);;

	//	//load arena first
	//	file.open("./Bitmaps/Arena.json");
	//	file >> jsonValue;
	//	file.close();

	//	for (Json::ValueIterator i = jsonValue.begin(); i != jsonValue.end(); ++i) {
	//		std::cout << i.name() << std::endl;
	//		
	//		const std::string name = i.name();

	//		Json::Value tmp = *i;
	//		count = 0;
	//		for (Json::ValueIterator j = tmp.begin(); j != tmp.end(); ++j) {
	//			Json::Value temp = *j;
	//			//tmp.
	//			std::cout << "\t" << j.name() << ": " << temp.asInt() << std::endl;
	//		}

	//		SDL_Rect box;
	//		std::vector<SDL_Rect> rects;
	//		box.h = Array[0]; //height
	//		box.w = Array[1]; //width
	//		box.x = Array[2]; //xoffset
	//		box.y = Array[3]; //yoffset		
	//		rects.push_back(box);
	//	
	//		AnimationFilm* anim = new AnimationFilm(bm, rects, name);
	//		films.insert(std::pair<std::string, AnimationFilm*>(name, anim));
	//	}

	//	//load crowd next
	//	Json::Value jsonValue2;
	//	file.open("./Bitmaps/ArenaCrowd.json");
	//	file >> jsonValue;
	//	file.close();

	//	for (Json::ValueIterator i = jsonValue2.begin(); i != jsonValue2.end(); ++i)
	//	{
	//		std::cout << i.name() << std::endl;

	//		const std::string name = i.name();

	//		Json::Value tmp = *i;
	//		count = 0;
	//		for (Json::ValueIterator j = tmp.begin(); j != tmp.end(); ++j)
	//		{
	//			Json::Value temp = *j;
	//			//tmp.
	//			std::cout << "\t" << j.name() << ": " << temp.asInt() << std::endl;
	//		}

	//		SDL_Rect box;
	//		std::vector<SDL_Rect> rects;
	//		for (int k = 1; k <= 3; k++) //crowd frames
	//		{
	//			box.h = Array[0]; //height
	//			box.w = Array[1]; //width
	//			box.x = Array[2]*k; //xoffset
	//			box.y = Array[3]*k; //yoffset		
	//			rects.push_back(box);
	//		}
	//		AnimationFilm* anim = new AnimationFilm(bm, rects, name);
	//		films.insert(std::pair<std::string, AnimationFilm*>(name, anim));
	//	}
	//}
	

public:
	static AnimationFilmHolder& Get(void) {
	static AnimationFilmHolder holder;
		return holder;
	}
	AnimationFilmHolder(void) {}
	~AnimationFilmHolder() { CleanUp(); }
	void Load(const std::string& catalogue, SDL_Renderer* rend) {

		/*if (catalogue == "Arena")
		{
			LoadArena(rend);
			return;
		}*/

		std::string path = catalogue + ".png";
		int offsetX = 89, offsetY = 149;

		Json::Value jsonValue;
		std::ifstream file;
		file.open(catalogue + ".json");
		file >> jsonValue;
		file.close();

		for (Json::ValueIterator i = jsonValue.begin(); i != jsonValue.end(); ++i) {
			//std::cout << i.name() << std::endl;
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
				//std::cout << "\t" << j.name() << ": " << temp.asInt() << std::endl;

				Array[count++] = temp.asInt();
			}

			for (int k = 0; k < Array[0]; k++) {
				if (i.name() == "Rope"){
					SDL_Rect box;
					box.x = (k)*offsetX*3 + Array[1];
					box.y = Array[2];
					box.w = offsetX*3;
					box.h = offsetY;
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