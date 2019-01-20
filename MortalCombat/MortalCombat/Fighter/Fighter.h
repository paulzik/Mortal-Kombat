#pragma once
//#include "../Animator/Sprites/Sprite/Sprite.h"
#include "../Animator/Sprites/AnimationFilms/AnimationFilmHolder.h"
#include "../Animator/Animator/AnimatorHolder.h"
#include "../Animator/Animator/FrameRangeAnimator.h"
#include "../InputManager/InputManager.h"
#include "../../Libraries/include/SDL.h"
#include "../StateTransition/StateTransition.h"

#define	FIGHTER_ACTION_DELAY_MSECS	150

enum FighterTag {SubZero, Scorpion};
enum Direction { none, left, right };
enum PlayerIndex { P1, P2 };

class Fighter final {
private:
	SDL_Renderer *Renderer;
	//TODO
	Sprite*			sprite = nullptr;
	std::string FighterName[2] = { "SubZero", "Scorpion" };
	int x = 50, y = 330;
	int px = 20, py = 280;
	static int index;

	std::string		nextAction;
	//engine2d::TickAnimator*		tickAnimator = nullptr;	// deferred firing actions; always dynamic
	//engine2d::TickAnimation		tickAnim;
	input::InputManager							inputController;
	logic::StateTransitions						stateTransitions;
	AnimationFilmHolder*						AFH;
	AnimatorHolder*								animator;
	typedef std::map<std::string, Animator*>	Animators;
	Animators*									animators;
	void										UpdateKeys();
						
	int										health;
	FighterTag									tag;
	bool										isAlive;
	int											numberOfWins;
	int											playerIndex;

	inline void InitializeCharacter(FighterTag _charName, SDL_Renderer * renderer) {
		AFH = new AnimationFilmHolder();
		//AnimationFilmHolder& AFH = AnimationFilmHolder::Get();
		AFH->Load("./Bitmaps/Clips/" + FighterName[_charName] + "/" + FighterName[_charName], renderer);

		//TODO: check json for animators

		//sprite = new Sprite(50, 330, AFH.GetFilm("Idle"));

		animators = new Animators();
		animators->insert(std::pair<std::string, Animator*>("Idle", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Walk", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("WalkReverse", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Punchrighthigh", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Punchlefthigh", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Kickmid", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Kickhigh", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Kickround", new FrameRangeAnimator(index++))); 
		animators->insert(std::pair<std::string, Animator*>("Uppercut", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Tackle", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Throw", new FrameRangeAnimator(index++)));
		//animators->at("punchrighthigh")->SetOnFinish([](Animator*, void* fighter = this) {
		//	ToBeRunning = ((Fighter*)fighter)->animators->at("idle");
		//	ToBeSuspended = ((Fighter*)fighter)->animators->at("punchrighthigh");
		//	scorpion->SetAnimFilm(((Fighter*)fighter)->AFH->GetFilm("Idle"));
		//	//direction = MOVE_DIR::none;
		//});
		std::map<std::string, Animation*> animations;

		if (playerIndex == P1)
		{
			animators->insert(std::pair<std::string, Animator*>("Rope", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("Getoverhere", new FrameRangeAnimator(index++)));

			animations.insert(std::pair<std::string, Animation*>("Idle", new FrameRangeAnimation(0, 6, 0, 0, 0.07f, true, 1)));
			animations.insert(std::pair<std::string, Animation*>("Walk", new FrameRangeAnimation(0, 8, 6, 0, 0.075f, true, 0)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverse", new FrameRangeAnimation(0, 8, -6, 0, 0.075f, true, 3)));

			animations.insert(std::pair<std::string, Animation*>("Punchrighthigh", new FrameRangeAnimation(0, 2, 0, 0, 0.06f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Punchlefthigh", new FrameRangeAnimation(0, 2, 0, 0, 0.06f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Kickmid", new FrameRangeAnimation(0, 5, 0, 0, 0.06f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Kickhigh", new FrameRangeAnimation(0, 5, 0, 0, 0.06f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Kickround", new FrameRangeAnimation(0, 8, 0, 0, 0.085f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Uppercut", new FrameRangeAnimation(0, 5, 0, 0, 0.085f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Tackle", new FrameRangeAnimation(0, 7, 0, 0, 0.085f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Throw", new FrameRangeAnimation(0, 7, 0, 0, 0.085f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Rope", new FrameRangeAnimation(0, 6, 0, 0, 0.085f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Getoverhere", new FrameRangeAnimation(0, 6, 0, 0, 0.085f, false, 2)));
		}
		else {
			animations.insert(std::pair<std::string, Animation*>("Idle", new FrameRangeAnimation(0, 11, 0, 0, 0.07f, true, 1)));
			animations.insert(std::pair<std::string, Animation*>("Walk", new FrameRangeAnimation(0, 8, 6, 0, 0.075f, true, 0)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverse", new FrameRangeAnimation(0, 8, -6, 0, 0.075f, true, 3)));

			animations.insert(std::pair<std::string, Animation*>("Punchrighthigh", new FrameRangeAnimation(0, 2, 0, 0, 0.055f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Punchlefthigh", new FrameRangeAnimation(0, 5, 0, 0, 0.055f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Kickmid", new FrameRangeAnimation(0, 11, 0, 0, 0.03f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Kickhigh", new FrameRangeAnimation(0, 5, 0, 0, 0.06f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Kickround", new FrameRangeAnimation(0, 8, 0, 0, 0.085f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Uppercut", new FrameRangeAnimation(0, 5, 0, 0, 0.085f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Tackle", new FrameRangeAnimation(0, 7, 0, 0, 0.085f, false, 2)));
			animations.insert(std::pair<std::string, Animation*>("Throw", new FrameRangeAnimation(0, 7, 0, 0, 0.085f, false, 2)));
			//animations.insert(std::pair<std::string, Animation*>("Rope", new FrameRangeAnimation(0, 6, 0, 0, 0.085f, false, 2)));

			x = 580;

		}
		float time = clock() / CLOCKS_PER_SEC;
		for (auto entry : *animators) {
			if (entry.first == "WalkReverse") {
				AnimationFilm* walkReverse = new AnimationFilm(*AFH->GetFilm("Walk"));
				((FrameRangeAnimator*)entry.second)->Start(new Sprite(x, y, walkReverse), (FrameRangeAnimation*)animations.at(entry.first), time, true);
			}
			else if(entry.first == "Rope") {
				int pos = x + 20;
				((FrameRangeAnimator*)entry.second)->Start(new Sprite(x, y, AFH->GetFilm(entry.first)), (FrameRangeAnimation*)animations.at(entry.first), time);
				((FrameRangeAnimator*)entry.second)->SetLogicState(stateTransitions);
			}
			else {
				((FrameRangeAnimator*)entry.second)->Start(new Sprite(x, y, AFH->GetFilm(entry.first)), (FrameRangeAnimation*)animations.at(entry.first), time);
				((FrameRangeAnimator*)entry.second)->SetLogicState(stateTransitions);
			}
			AnimatorHolder::Register(entry.second);
		}
	}

	void InitializeStateMachine(logic::StateTransitions* ST);

public:
	Fighter(FighterTag _tag, int playerIndex, SDL_Renderer *renderer);
	Fighter();
	bool PlayerIsAlive();
	void DamagePlayer(int damage);
	int GetHealth();

	void Update();
	
};