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
	//AnimationFilmHolder* AFH;
	AnimatorHolder* animator;
	typedef std::map<std::string, Animator*> Animators;
	Animators* animators;
	void UpdateKeys();

	float health;
	FighterTag tag;
	bool isAlive;
	int numberOfWins;

	inline void InitializeCharacter(FighterTag _charName, SDL_Renderer * renderer) {
		//AFH = new AnimationFilmHolder();
		AnimationFilmHolder& AFH = AnimationFilmHolder::Get();
		AFH.Load("./Bitmaps/Clips/Scorpion/" + FighterName[_charName], renderer);

		//TODO: check json for animators


		sprite = new Sprite(50, 350, AFH.GetFilm("Idle"));

		animators = new Animators();
		animators->insert(std::pair<std::string, Animator*>("idle", new FrameRangeAnimator()->SetType(animatortype_t::idle)));
		animators->insert(std::pair<std::string, Animator*>("walk", new FrameRangeAnimator()->SetType(animatortype_t::movement)));
		animators->insert(std::pair<std::string, Animator*>("walkReverse", new FrameRangeAnimator()->SetType(animatortype_t::movement)));
		animators->insert(std::pair<std::string, Animator*>("punchrighthigh", new FrameRangeAnimator()->SetType(animatortype_t::action)));
		animators->insert(std::pair<std::string, Animator*>("punchlefthigh", new FrameRangeAnimator()->SetType(animatortype_t::action)));
		//animators->at("punchrighthigh")->SetOnFinish([](Animator*, void* fighter = this) {
		//	ToBeRunning = ((Fighter*)fighter)->animators->at("idle");
		//	ToBeSuspended = ((Fighter*)fighter)->animators->at("punchrighthigh");
		//	scorpion->SetAnimFilm(((Fighter*)fighter)->AFH->GetFilm("Idle"));
		//	//direction = MOVE_DIR::none;
		//});

		std::map<std::string, Animation*> animations;
		animations.insert(std::pair<std::string, Animation*>("idle", new FrameRangeAnimation(0, 6, 0, 0, 0.075f, true, 1)));
		animations.insert(std::pair<std::string, Animation*>("walk", new FrameRangeAnimation(0, 8, 6, 0, 0.075f, true, 0)));
		animations.insert(std::pair<std::string, Animation*>("walkReverse", new FrameRangeAnimation(0, 8, -6, 0, 0.075f, true, 3)));
		animations.insert(std::pair<std::string, Animation*>("punchrighthigh", new FrameRangeAnimation(0, 2, 0, 0, 0.06f, false, 2)));
		animations.insert(std::pair<std::string, Animation*>("punchlefthigh", new FrameRangeAnimation(0, 5, 0, 0, 0.06f, false, 2)));

		float time = clock() / CLOCKS_PER_SEC;
		for (auto entry : *animators) {
			((FrameRangeAnimator*)entry.second)->Start(sprite, (FrameRangeAnimation*)animations.at(entry.first), time);
			AnimatorHolder::Register(entry.second);
		}
	}

public:
	Fighter(FighterTag _tag, SDL_Renderer *renderer);
	bool PlayerIsAlive();
	void DamagePlayer(int damage);
	float GetHealth();

	void Update();
	
};