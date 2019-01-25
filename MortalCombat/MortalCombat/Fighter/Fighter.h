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
#include "../Animator/Animator/MovingPathAnimator.h"
#include "../Animator/AnimationTypes/MovingPathAnimation.h"
#include "../Configuration/ConfigAPIs.h"
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
	int wins;
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
	bool										deadFlag;
	FighterTag									tag;
	bool										isAlive;
	int											numberOfWins;
	int											playerIndex;
	bool isFlipped = false;
	float timer = 0;
	Direction direction = Direction::none;

	Animator* currAnimator;
	bool IsInAction;
	bool IsCrouching = false;
	bool IsBlocking = false;



	inline void InitializeCharacter(FighterTag _charName, SDL_Renderer * renderer) {
		AFH = new AnimationFilmHolder();
		Sprites = new SpritesHolder();
		//AnimationFilmHolder& AFH = AnimationFilmHolder::Get();
		AFH->Load("./Bitmaps/Clips/" + FighterName[_charName] + "/" + FighterName[_charName], renderer);
		if (FighterName[_charName] == "Scorpion") {
			wins = ConfigAPIs::Get().front()->GetPlayerWins(1);
		}
		else {
			wins = ConfigAPIs::Get().front()->GetPlayerWins(2);
		}
			

		animators = new Animators();
		animators->insert(std::pair<std::string, Animator*>("Idle", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Blockhigh", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Duck", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Blocklow", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("JumpForth", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Punchrighthigh", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Punchlefthigh", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Punchrightmid", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Punchleftmid", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Kickmid", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Kickhigh", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Kickround", new FrameRangeAnimator(index++))); 
		animators->insert(std::pair<std::string, Animator*>("Uppercut", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Tackle", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Throw", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Punchjump", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Dmgspecial", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Dmghigh", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Dmgmid", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Dmglow", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Dizzy", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Jesus", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Dmgduck", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Fallback", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("FallbackR", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("FallbackMove", new MovingPathAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("FallbackRMove", new MovingPathAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Fallside", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Fallthrow", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Getup", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Death", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Win", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("JumpForth", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("JumpForthMove", new MovingPathAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("Jump", new FrameRangeAnimator(index++)));
		animators->insert(std::pair<std::string, Animator*>("JumpMove", new MovingPathAnimator(index++)));

		std::map<std::string, Animation*> animations;
		animations.insert(std::pair<std::string, Animation*>("Jump", new FrameRangeAnimation(0, 4, 0, 0, 0.35f, false, index++)));
		animations.insert(std::pair<std::string, Animation*>("JumpMove", new MovingPathAnimation(0, 0, 0.02f, false, index++)));
		animations.insert(std::pair<std::string, Animation*>("JumpForth", new FrameRangeAnimation(0, 9, 0, 0, 0.08f, false, index++)));
		animations.insert(std::pair<std::string, Animation*>("JumpForthMove", new MovingPathAnimation(2, 0, 0.02f, false, index++)));
		animations.insert(std::pair<std::string, Animation*>("Death", new FrameRangeAnimation(0, 6, 0, 0, 0.075f, false, index++, true)));
		animations.insert(std::pair<std::string, Animation*>("Win", new FrameRangeAnimation(0, 4, 0, 0, 0.075f, false, index++, true)));

		if (playerIndex == P1)
		{
			animators->insert(std::pair<std::string, Animator*>("Rope", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("Burn", new FrameRangeAnimator(index++)));

			
			
			animators->insert(std::pair<std::string, Animator*>("WalkR", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkRMove", new MovingAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkL", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkLMove", new MovingAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseR", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseRMove", new MovingAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseL", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("WalkReverseLMove", new MovingAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("Frozen", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("FatalFrozen", new FrameRangeAnimator(index++)));

			animations.insert(std::pair<std::string, Animation*>("Idle", new FrameRangeAnimation(0, 7, 0, 0, 0.07f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("Blockhigh", new FrameRangeAnimation(0, 4, 0, 0, 0.07f, false, index++, true)));
			animations.insert(std::pair<std::string, Animation*>("Duck", new FrameRangeAnimation(0, 4, 0, 0, 0.03f, false, index++, true)));
			animations.insert(std::pair<std::string, Animation*>("Blocklow", new FrameRangeAnimation(0, 2, 0, 0, 0.07f, false, index++, true)));
			animations.insert(std::pair<std::string, Animation*>("WalkR", new FrameRangeAnimation(0, 8, 0, 0, 0.065f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkRMove", new MovingAnimation(2, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkL", new FrameRangeAnimation(0, 8, 0, 0, 0.065f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkLMove", new MovingAnimation(-2, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseR", new FrameRangeAnimation(0, 8, 0, 0, 0.065f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseRMove", new MovingAnimation(2, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseL", new FrameRangeAnimation(0, 8, 0, 0, 0.065f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseLMove", new MovingAnimation(-2, 0, 0.01f, true, index++)));


			animations.insert(std::pair<std::string, Animation*>("Frozen", new FrameRangeAnimation(0, 8, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("FatalFrozen", new FrameRangeAnimation(0, 10, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Dmgspecial", new FrameRangeAnimation(0, 3, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Dmgmid", new FrameRangeAnimation(0, 4, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Dmglow", new FrameRangeAnimation(0, 2, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Dmghigh", new FrameRangeAnimation(0, 6, 0, 0, 0.05f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Dizzy", new FrameRangeAnimation(0, 7, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Jesus", new FrameRangeAnimation(0, 3, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Dmgduck", new FrameRangeAnimation(0, 3, 0, 0, 0.075f, false, index++)));

			animations.insert(std::pair<std::string, Animation*>("Fallback", new FrameRangeAnimation(0, 6, 0, 0, 0.2f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("FallbackR", new FrameRangeAnimation(0, 6, 0, 0, 0.2f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("FallbackMove", new MovingPathAnimation(-1, 0, 0.02f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("FallbackRMove", new MovingPathAnimation(1, 0, 0.02f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Fallthrow", new FrameRangeAnimation(0, 7, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Fallside", new FrameRangeAnimation(0, 6, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Getup", new FrameRangeAnimation(0, 5, 0, 0, 0.075f, false, index++)));

			animations.insert(std::pair<std::string, Animation*>("Punchjump", new FrameRangeAnimation(0, 3, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Throw", new FrameRangeAnimation(0, 7, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Punchrighthigh", new FrameRangeAnimation(0, 3, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Punchlefthigh", new FrameRangeAnimation(0, 2, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Punchrightmid", new FrameRangeAnimation(0, 1, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Punchleftmid", new FrameRangeAnimation(0, 2, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickmid", new FrameRangeAnimation(0, 6, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickhigh", new FrameRangeAnimation(0, 6, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickround", new FrameRangeAnimation(0, 9, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Uppercut", new FrameRangeAnimation(0, 6, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Tackle", new FrameRangeAnimation(0, 8, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Throw", new FrameRangeAnimation(0, 8, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Rope", new FrameRangeAnimation(0, 12, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Burn", new FrameRangeAnimation(0, 21, 0, 0, 0.15f, false, index++)));


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
			animators->insert(std::pair<std::string, Animator*>("Kickslide", new FrameRangeAnimator(index++)));
			animators->insert(std::pair<std::string, Animator*>("Burned", new FrameRangeAnimator(index++)));

			animations.insert(std::pair<std::string, Animation*>("Dmgspecial", new FrameRangeAnimation(0, 3, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Dmgmid", new FrameRangeAnimation(0, 4, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Dmglow", new FrameRangeAnimation(0, 2, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Dmghigh", new FrameRangeAnimation(0, 6, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Dizzy", new FrameRangeAnimation(0, 7, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Jesus", new FrameRangeAnimation(0, 3, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Dmgduck", new FrameRangeAnimation(0, 3, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Burned", new FrameRangeAnimation(0, 9, 0, 0, 0.075f, false, index++)));

			animations.insert(std::pair<std::string, Animation*>("Fallback", new FrameRangeAnimation(0, 6, 0, 0, 0.2f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("FallbackR", new FrameRangeAnimation(0, 6, 0, 0, 0.2f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("FallbackMove", new MovingPathAnimation(-1, 0, 0.02f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("FallbackRMove", new MovingPathAnimation(1, 0, 0.02f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Fallthrow", new FrameRangeAnimation(0, 7, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Fallside", new FrameRangeAnimation(0, 6, 0, 0, 0.075f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Getup", new FrameRangeAnimation(0, 5, 0, 0, 0.075f, false, index++)));

			animations.insert(std::pair<std::string, Animation*>("Punchjump", new FrameRangeAnimation(0, 3, 0, 0, 0.06f, false, index++)));
			animators->insert(std::pair<std::string, Animator*>("Freezeball", new FrameRangeAnimator(index++)));

			animations.insert(std::pair<std::string, Animation*>("Idle", new FrameRangeAnimation(0, 11, 0, 0, 0.07f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("Blockhigh", new FrameRangeAnimation(0, 4, 0, 0, 0.07f, false, index++, true)));
			animations.insert(std::pair<std::string, Animation*>("Duck", new FrameRangeAnimation(0, 4, 0, 0, 0.03f, false, index++, true)));
			animations.insert(std::pair<std::string, Animation*>("Blocklow", new FrameRangeAnimation(0, 2, 0, 0, 0.07f, false, index++, true)));
			animations.insert(std::pair<std::string, Animation*>("WalkR", new FrameRangeAnimation(0, 8, 0, 0, 0.065f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkRMove", new MovingAnimation(2, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkL", new FrameRangeAnimation(0, 8, 0, 0, 0.065f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkLMove", new MovingAnimation(-2, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseR", new FrameRangeAnimation(0, 8, 0, 0, 0.065f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseRMove", new MovingAnimation(2, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseL", new FrameRangeAnimation(0, 8, 0, 0, 0.065f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("WalkReverseLMove", new MovingAnimation(-2, 0, 0.01f, true, index++)));
			animations.insert(std::pair<std::string, Animation*>("Punchrighthigh", new FrameRangeAnimation(0, 2, 0, 0, 0.055f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Punchlefthigh", new FrameRangeAnimation(0, 5, 0, 0, 0.055f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Punchrightmid", new FrameRangeAnimation(0, 1, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Punchleftmid", new FrameRangeAnimation(0, 2, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickmid", new FrameRangeAnimation(0, 6, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickhigh", new FrameRangeAnimation(0, 6, 0, 0, 0.06f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickround", new FrameRangeAnimation(0, 8, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Uppercut", new FrameRangeAnimation(0, 5, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Tackle", new FrameRangeAnimation(0, 8, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Throw", new FrameRangeAnimation(0, 7, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Kickslide", new FrameRangeAnimation(0, 2, 0, 0, 0.085f, false, index++)));
			animations.insert(std::pair<std::string, Animation*>("Freezeball", new FrameRangeAnimation(0, 12, 0, 0, 0.085f, false, index++)));

			//animations.insert(std::pair<std::string, Animation*>("Rope", new FrameRangeAnimation(0, 6, 0, 0, 0.085f, false, index++)));

			positionX = 580;
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
				((MovingPathAnimator*)entry.second)->Start(s, (MovingPathAnimation*)animations.at(entry.first), time);
				((MovingPathAnimator*)entry.second)->SetLogicState(stateTransitions);
				Sprites->Add(s, 0);

			}
			else if (entry.first == "JumpForthMove") {
				Sprite* s = new Sprite(positionX, positionY, AFH->GetFilm("JumpForth"), isFlipped);
				((MovingPathAnimator*)entry.second)->Start(s, (MovingPathAnimation*)animations.at(entry.first), time);
				((MovingPathAnimator*)entry.second)->SetLogicState(stateTransitions);
				Sprites->Add(s, 0);

			}
			else if (entry.first == "FallbackMove" || entry.first == "FallbackRMove" ) {
				Sprite* s = new Sprite(positionX, positionY, AFH->GetFilm("Fallback"), isFlipped);
				((MovingPathAnimator*)entry.second)->Start(s, (MovingPathAnimation*)animations.at(entry.first), time);
				((MovingPathAnimator*)entry.second)->SetLogicState(stateTransitions);
				Sprites->Add(s, 0);

			}
			else if (entry.first == "FallbackR") {
				Sprite* s = new Sprite(positionX, positionY, AFH->GetFilm("Fallback"), isFlipped);
				((FrameRangeAnimator*)entry.second)->Start(s, (FrameRangeAnimation*)animations.at(entry.first), time);
				((FrameRangeAnimator*)entry.second)->SetLogicState(stateTransitions);
				Sprites->Add(s, 0);

			}
			else if (entry.first == "Death") {
				Sprite* s = new Sprite(positionX, positionY, AFH->GetFilm("Fallback"), isFlipped);
				((FrameRangeAnimator*)entry.second)->Start(s, (FrameRangeAnimation*)animations.at(entry.first), time);
				((FrameRangeAnimator*)entry.second)->SetLogicState(stateTransitions);
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
	void DamageOpponent(int damage, std::queue<Animator*> animQueue);
	int GetHealth();
	int GetWins();
	logic::StateTransitions* GetState() {
		return &stateTransitions;
	}
	Animators* GetAnimators() {
		return animators;
	}
	void InitializeStateMachineScorpion(logic::StateTransitions* ST);
	void InitializeStateMachineSubZero(logic::StateTransitions* ST);
	void AddKey(std::string _key) {
		timer = float((float)clock() / (float)CLOCKS_PER_SEC);
		inputController.buttons.push_back(_key);
	}
	bool pressed;
	void AddMove(std::string _key) {
		if (health > 0 && opponent->health > 0)
		{

			if (direction == none)
				if (_key == "d" || _key == "l") {
					direction = Direction::right;
				}
				else if (_key == "a" || _key == "j") {
					if (direction == none)
						direction = Direction::left;
				}
				else if ((_key == "q" || _key == "o") && !IsBlocking) {
					IsBlocking = true;
					//AnimatorHolder::MarkAsSuspended(animators->at("Idle"));
					//AnimatorHolder::MarkAsRunning(animators->at("Blockhigh"));
					inputController.buttons.push_back(_key);
					pressed = true;
					timer = float((float)clock() / (float)CLOCKS_PER_SEC);
					if (!IsCrouching)
						animators->at("Blockhigh")->SetState(animatorstate_t::ANIMATOR_RUNNING);
					else {
						AnimatorHolder::MarkAsSuspended(animators->at("Duck"));

						animators->at("Duck")->SetState(animatorstate_t::ANIMATOR_FINISHED);
						animators->at("Blocklow")->SetState(animatorstate_t::ANIMATOR_RUNNING);
						AnimatorHolder::MarkAsSuspended(animators->at("Idle"));
					}
				}
				else if ((_key == "s" || _key == "k") && !IsCrouching) {
					IsCrouching = true;
					//AnimatorHolder::MarkAsSuspended(animators->at("Idle"));
					//AnimatorHolder::MarkAsRunning(animators->at("Blockhigh"));
					AnimatorHolder::MarkAsRunning(animators->at("Duck"));
					animators->at("Duck")->SetState(animatorstate_t::ANIMATOR_RUNNING);
				}

			if (!pressed) {
				inputController.buttons.push_back(_key);
				pressed = true;

				timer = float((float)clock() / (float)CLOCKS_PER_SEC);
			}
		}

	}

	void RemoveMove(std::string _key) {
		if ((_key == "d" || _key == "l") && direction == Direction::right) {
			direction = Direction::none;
		}
		else if ((_key == "a" || _key == "j") && direction == Direction::left) {
			direction = Direction::none;
		}
		else if ((_key == "q" || _key == "o") ) {
			IsBlocking = false;
			/*AnimatorHolder::MarkAsSuspended(animators->at("Blockhigh"));
			AnimatorHolder::MarkAsRunning(animators->at("Idle"));
			stateTransitions.SetState("Idle");*/
			if (!IsCrouching)
				animators->at("Blockhigh")->SetState(animatorstate_t::ANIMATOR_FINISHED);
			else {
				AnimatorHolder::MarkAsRunning(animators->at("Duck"));
				stateTransitions.SetState("Duck");
				animators->at("Blocklow")->SetState(animatorstate_t::ANIMATOR_FINISHED);
				//animators->at("Blocklow")->Stop();
			}
		}
		else if ((_key == "s" || _key == "k")) {
			IsCrouching = false;
			/*AnimatorHolder::MarkAsSuspended(animators->at("Blockhigh"));
			AnimatorHolder::MarkAsRunning(animators->at("Idle"));
			stateTransitions.SetState("Idle");*/
			animators->at("Duck")->SetState(animatorstate_t::ANIMATOR_FINISHED);
			//animators->at("Duck")->Stop();
			stateTransitions.SetState("Idle");
			AnimatorHolder::MarkAsSuspended(animators->at("Blockhigh"));
			AnimatorHolder::MarkAsSuspended(animators->at("Blocklow"));
			AnimatorHolder::MarkAsSuspended(animators->at("Duck"));
			AnimatorHolder::MarkAsRunning(animators->at("Idle"));
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


	int positionX = 80, positionY = 330;
	std::queue<Animator*> RunningQueue;
	std::queue<Animator*> MovingQueue;

	void StopAll() {
		for (std::map<std::string, Animator*>::iterator it = animators->begin(); it != animators->end(); ++it) {
			AnimatorHolder::MarkAsSuspended(it->second);
		}
	}
};