#pragma once
//#include "../Animator/Sprites/Sprite/Sprite.h"
#include "../Animator/Sprites/AnimationFilms/AnimationFilmHolder.h"
#include "../Animator/Animator/AnimatorHolder.h"
#include "../Animator/Animator/FrameRangeAnimator.h"
#include "../InputManager/InputManager.h"
#include "../../Libraries/include/SDL.h"

#define	FIGHTER_ACTION_DELAY_MSECS	150

enum FighterTag {SubZero, Scorpion};
enum Direction { none, left, right };

class Fighter final {
private:
	SDL_Renderer *Renderer;
	//TODO
	Sprite*			sprite = nullptr;
	std::string FighterName[2] = { "SubZero", "Scorpion" };


	std::string		nextAction;
	//engine2d::TickAnimator*		tickAnimator = nullptr;	// deferred firing actions; always dynamic
	//engine2d::TickAnimation		tickAnim;
	input::InputManager			inputController;
	//logic::StateTransitions		stateTransitions;
	AnimationFilmHolder* AFH;
	AnimatorHolder* animator;
	typedef std::map<std::string, Animator*> Animators;
	Animators* animators;

	float health;
	FighterTag tag;
	bool isAlive;
	int numberOfWins;

	inline void InitializeCharacter(FighterTag _charName, SDL_Renderer * renderer) {
		AFH = new AnimationFilmHolder();
		AFH->Load("./Bitmaps/Clips/Scorpion/" + FighterName[_charName], renderer);

		//TODO: check json for animators

		sprite = new Sprite(0, 0, AFH->GetFilm("Idle"));
		animators = new Animators();
		animators->insert(std::pair<std::string, Animator*>("idle", new FrameRangeAnimator()));
		animators->insert(std::pair<std::string, Animator*>("walk", new FrameRangeAnimator()));
		animators->insert(std::pair<std::string, Animator*>("walkReverse", new FrameRangeAnimator()));
		animators->insert(std::pair<std::string, Animator*>("punchrighthigh", new FrameRangeAnimator()));
		//animators->at("punchrighthigh")->SetOnFinish([](Animator*, void* fighter = this) {
		//	ToBeRunning = ((Fighter*)fighter)->animators->at("idle");
		//	ToBeSuspended = ((Fighter*)fighter)->animators->at("punchrighthigh");
		//	scorpion->SetAnimFilm(((Fighter*)fighter)->AFH->GetFilm("Idle"));
		//	//direction = MOVE_DIR::none;
		//});

		std::map<std::string, Animation*> animations;
		animations.insert(std::pair<std::string, Animation*>("idle", new FrameRangeAnimation(0, 6, 0, 0, 0.075f, true, 1)));
		animations.insert(std::pair<std::string, Animation*>("walk", new FrameRangeAnimation(0, 8, 4, 0, 0.1f, true, 0)));
		animations.insert(std::pair<std::string, Animation*>("walkReverse", new FrameRangeAnimation(0, 8, -4, 0, 0.075f, true, 3)));
		animations.insert(std::pair<std::string, Animation*>("punchrighthigh", new FrameRangeAnimation(0, 2, 0, 0, 0.5f, false, 2)));

		float time = clock() / CLOCKS_PER_SEC;
		for (auto entry : *animators) {
			((FrameRangeAnimator*)entry.second)->Start(sprite, (FrameRangeAnimation*)animations.at(entry.first), time);
			animator->Register(entry.second);
		}
	}

public:
	Fighter(FighterTag _tag, SDL_Renderer *renderer);
	bool PlayerIsAlive();
	void DamagePlayer(int damage);
	float GetHealth();

	void Update();
	
};