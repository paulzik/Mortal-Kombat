#pragma once
//#include "../Animator/Sprites/Sprite/Sprite.h"
#include "../Animator/Sprites/AnimationFilms/AnimationFilmHolder.h"
#include "../Animator/Animator/AnimatorHolder.h"
#include "../Animator/Animator/FrameRangeAnimator.h"
#include "../InputManager/InputManager.h"
#include "../../Libraries/include/SDL.h"
#include "../StateTransition/StateTransition.h"
#include "../Animator/Sprites/Sprite/SpritesHolder.h"
#include "../Animator/Animator/MovingAnimator.h"
#include <queue>

#define	FIGHTER_ACTION_DELAY_MSECS	150

enum FighterTag {SubZero, Scorpion};
enum Direction { none, left, right };
enum PlayerIndex { P1, P2 };

class Fighter final {
private:
	SDL_Renderer *Renderer;
	//TODO
	Sprite*			sprite = nullptr;
	SpritesHolder* Sprites;
	std::string FighterName[2] = { "SubZero", "Scorpion" };

	static int index;
	bool rightIsForward = false;
	Fighter* opponent;
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
	bool isFlipped = false;
	float timer = 0;
	Direction direction = Direction::none;
	std::queue<Animator*> RunningQueue;
	std::queue<Animator*> MovingQueue;
	Animator* currAnimator;
	bool IsInAction;



	inline void InitializeCharacter(FighterTag _charName, SDL_Renderer * renderer) {
		AFH = new AnimationFilmHolder();
		Sprites = new SpritesHolder();
		//AnimationFilmHolder& AFH = AnimationFilmHolder::Get();
		AFH->Load("./Bitmaps/Clips/" + FighterName[_charName] + "/" + FighterName[_charName], renderer);

		//TODO: check json for animators

		//sprite = new Sprite(50, 330, AFH.GetFilm("Idle"));

		animators = new Animators();
		animators->insert(std::pair<std::string, Animator*>("Idle", new FrameRangeAnimator(index++)));

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
			animators->insert(std::pair<std::string, Animator*>("Burn", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("Jump", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("JumpMove", new MovingAnimator(index++)));

			animators->insert(std::pair<std::string, Animator*>("WalkR", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkRMove", new MovingAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkL", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkLMove", new MovingAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseR", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseRMove", new MovingAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseL", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseLMove", new MovingAnimator(index++)));

			animations.insert(std::pair<std::string, Animation*>("Idle", new FrameRangeAnimation(0, 7, 0, 0, 0.07f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkR", new FrameRangeAnimation(0, 8, 0, 0, 0.075f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkRMove", new MovingAnimation(1, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkL", new FrameRangeAnimation(0, 8, 0, 0, 0.075f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkLMove", new MovingAnimation(-1, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseR", new FrameRangeAnimation(0, 8, 0, 0, 0.075f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseRMove", new MovingAnimation(1, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseL", new FrameRangeAnimation(0, 8, 0, 0, 0.075f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseLMove", new MovingAnimation(-1, 0, 0.01f, true, index++)));

			animations.insert(std::pair<std::string, Animation*>("Punchrighthigh", new FrameRangeAnimation(0, 3, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Punchlefthigh", new FrameRangeAnimation(0, 3, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickmid", new FrameRangeAnimation(0, 6, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickhigh", new FrameRangeAnimation(0, 6, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickround", new FrameRangeAnimation(0, 9, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Uppercut", new FrameRangeAnimation(0, 6, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Tackle", new FrameRangeAnimation(0, 8, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Throw", new FrameRangeAnimation(0, 8, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Rope", new FrameRangeAnimation(0, 12, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Burn", new FrameRangeAnimation(0, 21, 0, 0, 0.15f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Jump", new FrameRangeAnimation(0, 3, 0, 0, 0.3f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("JumpMove", new MovingAnimation(0, -4, 0.04f, false, index++)));
			rightIsForward = true;

		}
		else {
			animators->insert(std::pair<std::string, Animator*>("WalkR", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkRMove", new MovingAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkL", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkLMove", new MovingAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseR", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseRMove", new MovingAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseL", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseLMove", new MovingAnimator(index++)));

			animations.insert(std::pair<std::string, Animation*>("Idle", new FrameRangeAnimation(0, 11, 0, 0, 0.07f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkR", new FrameRangeAnimation(0, 8, 0, 0, 0.075f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkRMove", new MovingAnimation(1, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkL", new FrameRangeAnimation(0, 8, 0, 0, 0.075f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkLMove", new MovingAnimation(-1, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseR", new FrameRangeAnimation(0, 8, 0, 0, 0.075f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseRMove", new MovingAnimation(1, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseL", new FrameRangeAnimation(0, 8, 0, 0, 0.075f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseLMove", new MovingAnimation(-1, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("Punchrighthigh", new FrameRangeAnimation(0, 2, 0, 0, 0.055f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Punchlefthigh", new FrameRangeAnimation(0, 5, 0, 0, 0.055f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickmid", new FrameRangeAnimation(0, 6, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickhigh", new FrameRangeAnimation(0, 6, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickround", new FrameRangeAnimation(0, 8, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Uppercut", new FrameRangeAnimation(0, 5, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Tackle", new FrameRangeAnimation(0, 7, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Throw", new FrameRangeAnimation(0, 7, 0, 0, 0.085f, false, index++)));
			//animations.insert(std::pair<std::string, Animation*>("Rope", new FrameRangeAnimation(0, 6, 0, 0, 0.085f, false, index++)));

			positionX = 350;
		}
		float time = clock() / CLOCKS_PER_SEC;
		for (auto entry : *animators) {
			if (entry.first == "WalkReverseR" || entry.first == "WalkReverseL" || entry.first == "WalkReverseRMove" || entry.first == "WalkReverseLMove") {
				AnimationFilm* walkReverse = new AnimationFilm(*AFH->GetFilm("Walk"));
				Sprite * s = new Sprite(positionX, positionY, walkReverse, isFlipped);
				((FrameRangeAnimator*)entry.second)->Start(s, (FrameRangeAnimation*)animations.at(entry.first), time, true);
				Sprites->Add(s, 0);
			}
			else if(entry.first == "Getoverhere" && playerIndex == P1) {
				Sprite * s = new Sprite(positionX, positionY, AFH->GetFilm(entry.first), isFlipped);
				((FrameRangeAnimator*)entry.second)->Start(s, (FrameRangeAnimation*)animations.at(entry.first), time);
				((FrameRangeAnimator*)entry.second)->SetLogicState(stateTransitions);
				Sprites->Add(s, 0);

			}
			else if (entry.first == "WalkL" || entry.first == "WalkR" || entry.first == "WalkLMove" || entry.first == "WalkRMove") {
				Sprite* s = new Sprite(positionX, positionY, AFH->GetFilm("Walk"), isFlipped);
				((FrameRangeAnimator*)entry.second)->Start(s, (FrameRangeAnimation*)animations.at(entry.first), time);
				((FrameRangeAnimator*)entry.second)->SetLogicState(stateTransitions);
				Sprites->Add(s, 0);

			}
			else if (entry.first == "JumpMove") {
				Sprite* s = new Sprite(positionX, positionY, AFH->GetFilm("Jump"), isFlipped);
				((MovingAnimator*)entry.second)->Start(s, (MovingAnimation*)animations.at(entry.first), time);
				((MovingAnimator*)entry.second)->SetLogicState(stateTransitions);
				Sprites->Add(s, 0);

			}
			else {
				Sprite* s = new Sprite(positionX, positionY, AFH->GetFilm(entry.first), isFlipped);
				((FrameRangeAnimator*)entry.second)->Start(s, (FrameRangeAnimation*)animations.at(entry.first), time);
				((FrameRangeAnimator*)entry.second)->SetLogicState(stateTransitions);
				Sprites->Add(s, 0);

			}
			AnimatorHolder::Register(entry.second);
		}
	}

	void InitializeStateMachineScorpion(logic::StateTransitions* ST);
	void InitializeStateMachineSubZero(logic::StateTransitions* ST);

	void InitializeKeyCombinations();

	void StopMovement() {

		AnimatorHolder::MarkAsSuspended(animators->at("WalkR"));
		AnimatorHolder::MarkAsSuspended(animators->at("WalkRMove"));
		AnimatorHolder::MarkAsSuspended(animators->at("WalkReverseR"));
		AnimatorHolder::MarkAsSuspended(animators->at("WalkReverseRMove"));

		AnimatorHolder::MarkAsSuspended(animators->at("WalkL"));
		AnimatorHolder::MarkAsSuspended(animators->at("WalkLMove"));
		AnimatorHolder::MarkAsSuspended(animators->at("WalkReverseL"));
		AnimatorHolder::MarkAsSuspended(animators->at("WalkReverseLMove"));
	}

public:
	Fighter(FighterTag _tag, int playerIndex, SDL_Renderer *renderer);
	Fighter();
	bool PlayerIsAlive();
	void DamageOpponent(int damage);
	int GetHealth();

	void AddKey(std::string _key) {
		timer = float((float)clock() / (float)CLOCKS_PER_SEC);
		inputController.buttons.push_back(_key);
	}
	bool pressed;
	void AddMove(std::string _key) {
		if (_key == "d" || _key == "l") {
			direction = Direction::right;
		}
		else if (_key == "a" || _key == "j") {
			direction = Direction::left;
		}

		if (!pressed) {
			inputController.buttons.push_back(_key);
			pressed = true;

			timer = float((float)clock() / (float)CLOCKS_PER_SEC);
		}

	}

	void RemoveMove(std::string _key) {
		if ((_key == "d" || _key == "l") && direction == Direction::right) {
			direction = Direction::none;
		}
		else if ((_key == "a" || _key == "j") && direction == Direction::left) {
			direction = Direction::none;
		}
		pressed = false;

	}

	float CalculateDistanceWithOpponent()
	{
		float diffY = positionY - opponent->positionY;
		float diffX = positionX - opponent->positionX;
		return sqrt((diffY * diffY) + (diffX * diffX));
	}

	void SetOpponent(Fighter* _opponent) {
		opponent = _opponent;
	}


	void Update();

	void FlipCharacter(bool _flip) {
		//AFH->FlipFilms(!_flip);
		isFlipped = !_flip;
		SpritesHolder::SpriteList list;
		Sprites->GetSprites(0, &list);
		for (auto entry : list) {
			entry->SetFlipped(!_flip);
		}
		rightIsForward = _flip;
	}


	int positionX = 50, positionY = 330;
};