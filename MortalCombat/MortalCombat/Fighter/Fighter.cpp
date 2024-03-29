#include "Fighter.h"
#include "../SoundEngine/SoundEngine.h"
#include <algorithm>
#include <future>
#include <queue>
#include "../Configuration/ConfigAPIs.h"
#include "../UI/UIManager.h"

SDL_Joystick *joystick;

int Fighter::index = 0;

Animator* currAnimator2;
bool canDoActionP1 = true;
bool canDoActionP2 = true;

float timescale = 1.0f;

Fighter::Fighter(FighterTag _tag, int playerIndex, SDL_Renderer *renderer)
{

	SDL_JoystickEventState(SDL_ENABLE);
	joystick = SDL_JoystickOpen(0);
	deadFlag = false;
	using Input = logic::StateTransitions::Input;
	
	AnimationFilmHolder& AFH = AnimationFilmHolder::Get();
	tag = _tag;
	health = 100.0;
	isAlive = true;

	this->playerIndex = playerIndex;

	InitializeCharacter(_tag, renderer);

	std::string forward = rightIsForward ? "d" : "a";

	Renderer = renderer;

	InitializeKeyCombinations();

	stateTransitions.SetState("Idle");

	Sprite* s = sprite;
	AnimationFilmHolder* afh = &AFH;
	Animators* anim = animators;
	
	logic::StateTransitions *state = &stateTransitions;


}

bool Fighter::PlayerIsAlive()
{
	return isAlive;
}

void Fighter::DamageOpponent(int _damage, std::queue<Animator*> animQueue)
{
	int damage = _damage * 3;
	if (ConfigAPIs::Get().front()->GetGodMode())
		return;
	//Collisions
	if (CalculateDistanceWithOpponent() < 165 && opponent->IsBlocking == false) {
		
		opponent->health -= damage;
		if (deadFlag)
			return;
		if (opponent->health < 0) {
			opponent->health = 0;
			deadFlag = true;
			if (tag == FighterTag::Scorpion){
				SoundEngine::Get()->Play("./SoundEngine/Sounds/announcer/ScorpionWins.mp3");
				SoundEngine::Get()->Play("./SoundEngine/Sounds/arenas/Clapping1.mp3");
				UIManager::Get()->FireAnimation("scorpionwins", 0);
				ConfigAPIs::Get().front()->AddPlayerWin(1,1);
				if (ConfigAPIs::Get().front()->GetBetWinMode() == 1) {
					wins ++;
					ConfigAPIs::Get().front()->AddPlayerWin(1,1);
				}
				wins++;
				if (ConfigAPIs::Get().front()->GetBetWinMode() == 2) {
					opponent->wins--;
					if (opponent->wins < 0)
						opponent->wins = 0;
					ConfigAPIs::Get().front()->AddPlayerWin(2,-1);
				}
			}
			else{
				SoundEngine::Get()->Play("./SoundEngine/Sounds/announcer/SubzeroWins.mp3");
				SoundEngine::Get()->Play("./SoundEngine/Sounds/arenas/Clapping2.mp3");
				UIManager::Get()->FireAnimation("subzerowins", 0);
				ConfigAPIs::Get().front()->AddPlayerWin(2, 1);
				if (ConfigAPIs::Get().front()->GetBetWinMode() == 2) {
					wins++;
					ConfigAPIs::Get().front()->AddPlayerWin(2, 1);
				}
				wins++;
				if (ConfigAPIs::Get().front()->GetBetWinMode() == 1) {
					opponent->wins--;
					if (opponent->wins < 0)
						opponent->wins = 0;
					ConfigAPIs::Get().front()->AddPlayerWin(1, -1);
				}
			}

			ConfigAPIs::Get().front()->ExportConfigurationData();

			while (animQueue.size() != 0)
			{
				animQueue.pop();
			}
			animQueue.push(opponent->animators->at("Death"));
			this->RunningQueue.push(animators->at("Win"));
		}
		opponent->StopAll();
		if (animQueue.size() == 2)
		{
			opponent->RunningQueue.push(animQueue.front());
			animQueue.pop();
		}
		else if (animQueue.size() == 3)
		{
			opponent->RunningQueue.push(animQueue.front());
			animQueue.pop();
			opponent->MovingQueue.push(animQueue.front());
			animQueue.pop();
		}
		AnimatorHolder::MarkAsRunning(animQueue.front());
		opponent->currAnimator = animQueue.front();
		animQueue.pop();
		opponent->stateTransitions.SetState("Dmg");


	}
	else if (CalculateDistanceWithOpponent() < 165 && opponent->IsBlocking == true) {

		opponent->health -= damage / 3;

		//Set health back to zero to avoid visual bugs (lifebar)
		if (opponent->health < 0)
			opponent->health = 0;
	}

}
Fighter::Fighter()
{
}
int Fighter::GetHealth()
{
	return health;
}

int Fighter::GetWins()
{
	return wins;
}

void Fighter::Update()
{
	using Input = logic::StateTransitions::Input;



	AnimationFilmHolder& AFH = AnimationFilmHolder::Get();

	//UpdateKeys();
	if (direction == Direction::left) {
		AnimatorHolder::MarkAsSuspended(animators->at("Idle"));

		if (isFlipped)
		{
			AnimatorHolder::MarkAsRunning(animators->at("WalkL"));
			AnimatorHolder::MarkAsRunning(animators->at("WalkLMove"));
			AnimatorHolder::MarkAsSuspended(animators->at("WalkReverseL"));
			AnimatorHolder::MarkAsSuspended(animators->at("WalkReverseLMove"));
		}
		else {
			AnimatorHolder::MarkAsSuspended(animators->at("WalkL"));
			AnimatorHolder::MarkAsSuspended(animators->at("WalkLMove"));
			AnimatorHolder::MarkAsRunning(animators->at("WalkReverseL"));
			AnimatorHolder::MarkAsRunning(animators->at("WalkReverseLMove"));
		}
	}
	else if (direction == Direction::right) {
		AnimatorHolder::MarkAsSuspended(animators->at("Idle"));

		if (!isFlipped)
		{
			AnimatorHolder::MarkAsRunning(animators->at("WalkR"));
			AnimatorHolder::MarkAsRunning(animators->at("WalkRMove"));
			AnimatorHolder::MarkAsSuspended(animators->at("WalkReverseR"));
			AnimatorHolder::MarkAsSuspended(animators->at("WalkReverseRMove"));
		}
		else {
			AnimatorHolder::MarkAsSuspended(animators->at("WalkR"));
			AnimatorHolder::MarkAsSuspended(animators->at("WalkRMove"));
			AnimatorHolder::MarkAsRunning(animators->at("WalkReverseR"));
			AnimatorHolder::MarkAsRunning(animators->at("WalkReverseRMove"));
		}
	}
	else if (currAnimator == NULL) {
			AnimatorHolder::MarkAsRunning(animators->at("Idle"));

			StopMovement();
	}

	if (IsInAction) {
		StopMovement();
	}

	if (float((float)clock() / (float)CLOCKS_PER_SEC) - timer > (float)((float)FIGHTER_ACTION_DELAY_MSECS / 1000.0f)) {


		inputController.buttons.clear();
		//if (kayPressed[SDLK_a]) {
		//	inputController.buttons.push_back("a");
		//}
		//if (kayPressed[SDLK_d]) {
		//	inputController.buttons.push_back("d");
		//}

	}
	inputController.Handle();

	std::string str = "";
	for (std::list<std::string>::iterator it = inputController.buttons.begin(); it != inputController.buttons.end(); ++it) {
		if (std::next(it) == inputController.buttons.end()){
			str.append(*it);
		}
		else
			str.append(*it + ".");
	}

	stateTransitions.PerformTransitions(Input{ str }, false);

	if (currAnimator != NULL && currAnimator->GetState() == ANIMATOR_FINISHED)
	{
		AnimatorHolder::MarkAsSuspended(currAnimator);
		currAnimator = NULL;
	}
	
	int SIZE = RunningQueue.size();
	for (int i = 0; i < SIZE; i++) {
		if (currAnimator == NULL) {
			currAnimator = RunningQueue.front();
			RunningQueue.pop();
			AnimatorHolder::MarkAsRunning(currAnimator);
			IsInAction = true;
		}
		
	}
	if (currAnimator != NULL &&currAnimator->GetState() == ANIMATOR_FINISHED)
	{
		AnimatorHolder::MarkAsSuspended(currAnimator);
		currAnimator = NULL;
	}
	else if (currAnimator == NULL){
		IsInAction = false;
	}
	SIZE = MovingQueue.size();
	for (int i = 0; i < SIZE; i++) {
		if (currAnimator2 == NULL) {
			currAnimator2 = MovingQueue.front();
			MovingQueue.pop();
			AnimatorHolder::MarkAsRunning(currAnimator2);
		}
		
	}
	if (currAnimator2 != NULL && currAnimator2->GetState() == ANIMATOR_FINISHED)
	{
		AnimatorHolder::MarkAsSuspended(currAnimator2);
		currAnimator2 = NULL;
	}
	if (positionX < 10 ) {
		positionX = 10;
	}
	else if (positionX > 700) {
		positionX = 700;
	}
}
bool kayPressed[500000];

void Fighter::InitializeStateMachineScorpion(logic::StateTransitions* ST) {
	ST->SetState("Idle");
	Animators* anim = animators;
	bool* flip = &rightIsForward;
	using Input = logic::StateTransitions::Input;
	int* player = &playerIndex;
	std::queue<Animator*> *RunningQueue = &this->RunningQueue;
	std::queue<Animator*> *MovingQueue = &this->MovingQueue;;
	Animator* currAnim = currAnimator;
	Fighter* thisFighter = this;
	Fighter*& opposingFighter = opponent;
	bool& crouch = IsCrouching;
	ST->SetTransition("Idle", Input{ }, [anim, ST](void) {
		canDoActionP1 = true;
	});
	ST->SetTransition("Idle", Input{ "w" }, [anim, ST, RunningQueue, MovingQueue, currAnim](void) {
		if (currAnim == NULL) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			ST->SetState("Jump");
			RunningQueue->push(anim->at("Jump"));
			MovingQueue->push(anim->at("JumpMove"));
			canDoActionP1 = true;
		}
		//RunningQueue.push(anim->at("Idle"));
		
		
	});
	ST->SetTransition("Idle", Input{ "s" }, [anim, ST, RunningQueue, crouch](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1 && !crouch) {
			//RunningQueue->push(anim->at("Duck"));
			canDoActionP1 = true;
			ST->SetState("Duck");
			//SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}

	});
	ST->SetTransition("Duck", Input{  }, [anim, ST, RunningQueue](void) {
		//Do Nothing
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		AnimatorHolder::MarkAsSuspended(anim->at("Blocklow"));

	});
	ST->SetTransition("Duck", Input{ "q" }, [anim, ST, RunningQueue](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		AnimatorHolder::MarkAsSuspended(anim->at("Duck"));
		if (canDoActionP1) {
			AnimatorHolder::MarkAsRunning(anim->at("Blocklow"));
			canDoActionP1 = false;
			ST->SetState("Blocklow");
			//SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}

	});
	ST->SetTransition("Blocklow", Input{ }, [anim, ST, RunningQueue](void) {
		//Do Nothing
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));

	});
	ST->SetTransition("Blocklow", Input{ "1212" }, [anim, ST, RunningQueue](void) {
		//Do Nothing

	});
	ST->SetTransition("Idle", Input{ "q" }, [anim, ST, RunningQueue](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			RunningQueue->push(anim->at("Blockhigh"));
			canDoActionP1 = false;
			//SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}

	});

	ST->SetTransition("Idle", Input{ "d.w" }, [anim, ST, RunningQueue, MovingQueue, currAnim](void) {
		if (currAnim == NULL) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			ST->SetState("JumpForth");
			RunningQueue->push(anim->at("JumpForth"));
			MovingQueue->push(anim->at("JumpForthMove"));
			canDoActionP1 = true;
		}
		//RunningQueue.push(anim->at("Idle"));


	});
	ST->SetTransition("Jump", Input{ "w" }, [anim, ST, currAnim](void) {
		if (currAnim == NULL) {
			
		}
		//RunningQueue.push(anim->at("Idle"));
	});
	ST->SetTransition("Jump", Input{ "w.3" }, [anim, ST, RunningQueue](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			RunningQueue->push(anim->at("Punchjump"));
			canDoActionP1 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}

	});
	ST->SetTransition("Idle", Input{ "4" }, [anim, ST, RunningQueue, currAnim, thisFighter, opposingFighter](void) {
		if (canDoActionP1 && currAnim == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue->push(anim->at("Punchrighthigh"));
			//canDoAction = false;
			ST->SetState("Punchrighthigh");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmghigh"));
			thisFighter->DamageOpponent(3, animeQueue);
		}

	});
	ST->SetTransition("Punchrighthigh", Input{ "4.4" }, [anim, ST, RunningQueue, thisFighter, &opposingFighter](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			RunningQueue->push(anim->at("Punchlefthigh"));
			canDoActionP1 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmghigh"));
			thisFighter->DamageOpponent(3, animeQueue);
		}

	});
	ST->SetTransition("Idle", Input{ "3" }, [anim, ST, RunningQueue, currAnim, thisFighter, &opposingFighter](void) {
		if (canDoActionP1 && currAnim == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue->push(anim->at("Punchrightmid"));
			//canDoAction = false;
			ST->SetState("Punchrightmid");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmgmid"));
			thisFighter->DamageOpponent(3, animeQueue);
		}

	});
	ST->SetTransition("Punchrightmid", Input{ "3.3" }, [anim, ST, RunningQueue, thisFighter, &opposingFighter](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			RunningQueue->push(anim->at("Punchleftmid"));
			canDoActionP1 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmgmid"));
			thisFighter->DamageOpponent(3, animeQueue);
		}

	});
	ST->SetTransition("Idle", Input{ "5" }, [anim, ST, RunningQueue, currAnim, thisFighter, &opposingFighter](void) {
		if (canDoActionP1 && currAnim == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue->push(anim->at("Kickmid"));
			//canDoAction = false;
			ST->SetState("Kickmid");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00193.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmgmid"));
			thisFighter->DamageOpponent(3, animeQueue);

		}
	});
	ST->SetTransition("Idle", Input{ "d.5" }, [anim, ST, RunningQueue, currAnim](void) {
		if (canDoActionP1 && currAnim == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue->push(anim->at("Throw"));
			//canDoAction = false;
			ST->SetState("Throw");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00193.mp3", false);

		}
	});
	ST->SetTransition("Kickmid", Input{ "5.5" }, [anim, ST, RunningQueue, thisFighter, &opposingFighter](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			RunningQueue->push(anim->at("Kickhigh"));
			canDoActionP1 = false;
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmghigh"));
			thisFighter->DamageOpponent(4, animeQueue);
		}

	});
	ST->SetTransition("Idle", Input{ "a.6" }, [anim, ST, RunningQueue, thisFighter, &opposingFighter](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			RunningQueue->push(anim->at("Kickround"));
			canDoActionP1 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00193.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmghigh"));
			thisFighter->DamageOpponent(4, animeQueue);
		}

	});

	ST->SetTransition("Idle", Input{ "s.4" }, [anim, ST, RunningQueue, thisFighter, &opposingFighter](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			RunningQueue->push(anim->at("Uppercut"));
			canDoActionP1 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00208.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Getup"));
			if (thisFighter->isFlipped)
				animeQueue.push(opposingFighter->GetAnimators()->at("FallbackMove"));
			else
				animeQueue.push(opposingFighter->GetAnimators()->at("FallbackRMove"));

			animeQueue.push(opposingFighter->GetAnimators()->at("Fallback"));
			thisFighter->DamageOpponent(4, animeQueue);
		}

	});
	ST->SetTransition("Idle", Input{ "a.5" }, [anim, ST, RunningQueue, thisFighter, &opposingFighter](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			RunningQueue->push(anim->at("Tackle"));
			canDoActionP1 = false;
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Getup"));
			animeQueue.push(opposingFighter->GetAnimators()->at("Fallside"));
			thisFighter->DamageOpponent(4, animeQueue);
		}

	});
	ST->SetTransition("Idle", Input{ "w.w" }, [anim, ST, RunningQueue, this](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			StopAll();
			RunningQueue->push(anim->at("Burn"));
			canDoActionP1 = false;
		}

	});
	/*ST->SetTransition("Idle", Input{ "d" }, [anim, ST](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		ST->SetState("Walk");
	});*/
	ST->SetTransition("Walk", Input{ }, [anim, ST, flip, player](void) {
		if (*player == P1)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("WalkR"));
			AnimatorHolder::MarkAsSuspended(anim->at("WalkRMove"));
			AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseR"));
			AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseRMove"));
		}
		ST->SetState("Idle");
	});
	/*ST->SetTransition("Idle", Input{ "a" }, [anim, ST](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		ST->SetState("WalkRev");
	});*/
	ST->SetTransition("WalkRev", Input{ }, [anim, ST, player, flip](void) {
		if (*player == P1)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseLMove"));
			AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseL"));
			AnimatorHolder::MarkAsSuspended(anim->at("WalkL"));
			AnimatorHolder::MarkAsSuspended(anim->at("WalkLMove"));
		}
		ST->SetState("Idle");
	});
	ST->SetTransition("Walk", playerIndex == P1 ? Input{ "d" } : Input{ "j" }, [anim, ST, flip, player](void) {
		if (*player == P1)
		{
			if (*flip) {

				AnimatorHolder::MarkAsRunning(anim->at("WalkR"));
				AnimatorHolder::MarkAsRunning(anim->at("WalkRMove"));
				AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseR"));
				AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseRMove"));
			}
			else {
				AnimatorHolder::MarkAsSuspended(anim->at("WalkR"));
				AnimatorHolder::MarkAsSuspended(anim->at("WalkRMove"));
				AnimatorHolder::MarkAsRunning(anim->at("WalkReverseR"));
				AnimatorHolder::MarkAsRunning(anim->at("WalkReverseRMove"));
			}
		}
	});
	ST->SetTransition("Walk", playerIndex == P1 ? Input{ "d.5" } : Input{ "j" }, [anim, ST, RunningQueue](void) {
		if (canDoActionP1) {
			AnimatorHolder::MarkAsSuspended(anim->at("Walk"));
			RunningQueue->push(anim->at("Throw"));
			canDoActionP1 = false;
		}	});
	ST->SetTransition("WalkRev", playerIndex == P1 ? Input{ "a" } : Input{ "l" }, [anim, ST, flip, player](void) {
		if (*player == P1)
		{
			if (*flip) {
				AnimatorHolder::MarkAsSuspended(anim->at("WalkL"));
				AnimatorHolder::MarkAsSuspended(anim->at("WalkLMove"));
				AnimatorHolder::MarkAsRunning(anim->at("WalkReverseL"));
				AnimatorHolder::MarkAsRunning(anim->at("WalkReverseLMove"));
			}
			else {
				AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseL"));
				AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseLMove"));
				AnimatorHolder::MarkAsRunning(anim->at("WalkL"));
				AnimatorHolder::MarkAsRunning(anim->at("WalkLMove"));
			}
		}
	});
	ST->SetTransition("Idle", playerIndex == P1 ? Input{ "a.a.3" } : Input{ "l" }, [anim, ST, RunningQueue](void) {
		if (canDoActionP1) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			RunningQueue->push(anim->at("Rope"));
			canDoActionP1 = false;
			
			int r = rand() % 2;
			if (r == 0)
				SoundEngine::Get()->Play("SoundEngine/Sounds/scorpion/mk1-goh.mp3", false);
			else {
				SoundEngine::Get()->Play("SoundEngine/Sounds/scorpion/mk1-00446.mp3", false);
			}
		}	
	});
}

void Fighter::InitializeStateMachineSubZero(logic::StateTransitions * ST)
{
	ST->SetState("Idle");
	Animators* anim = animators;
	bool* flip = &rightIsForward;
	using Input = logic::StateTransitions::Input;
	int* player = &playerIndex;
	std::queue<Animator*> *RunningQueue = &this->RunningQueue;
	std::queue<Animator*> *MovingQueue = &this->MovingQueue;;
	Animator* currAnim = currAnimator;
	Fighter* thisFighter = this;
	Fighter* opposingFighter = opponent;

	ST->SetTransition("Idle", Input{ }, [anim, ST](void) {
		canDoActionP2 = true;
	});
	ST->SetTransition("Idle", Input{ "i" }, [anim, ST, RunningQueue, MovingQueue, currAnim](void) {
		if (currAnim == NULL) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			ST->SetState("Jump");
			RunningQueue->push(anim->at("Jump"));
			MovingQueue->push(anim->at("JumpMove"));
			canDoActionP2 = true;
		}
		//RunningQueue.push(anim->at("Idle"));


	});
	ST->SetTransition("Idle", Input{ "j.i" }, [anim, ST, RunningQueue, MovingQueue, currAnim](void) {
		if (currAnim == NULL) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			ST->SetState("JumpForth");
			RunningQueue->push(anim->at("JumpForth"));
			MovingQueue->push(anim->at("JumpForthMove"));
			canDoActionP2 = true;
		}
		//RunningQueue.push(anim->at("Idle"));


	});
	ST->SetTransition("Jump", Input{ "i.7" }, [anim, ST, RunningQueue](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Punchjump"));
			canDoActionP2 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}

	});
	ST->SetTransition("Idle", Input{ "7" }, [anim, ST, RunningQueue, currAnim, thisFighter, opposingFighter](void) {
		if (canDoActionP2 && currAnim == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue->push(anim->at("Punchrighthigh"));
			//canDoAction = false;
			ST->SetState("Punchrighthigh");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00214.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmghigh"));
			thisFighter->DamageOpponent(3, animeQueue);
		}

	});
	ST->SetTransition("Idle", Input{ "0" }, [anim, ST, RunningQueue, currAnim, thisFighter, opposingFighter](void) {
		if (canDoActionP2 && currAnim == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue->push(anim->at("Punchrightmid"));
			//canDoAction = false;
			ST->SetState("Punchrightmid");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00214.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmgmid"));
			thisFighter->DamageOpponent(3, animeQueue);
		}

	});
	ST->SetTransition("Punchrightmid", Input{ "0.0" }, [anim, ST, RunningQueue, thisFighter, opposingFighter](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Punchleftmid"));
			canDoActionP2 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00214.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmgmid"));
			thisFighter->DamageOpponent(3, animeQueue);
		}

	});
	ST->SetTransition("Idle", Input{ "k" }, [anim, ST, RunningQueue](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Duck"));
			canDoActionP2 = true;
			ST->SetState("Duck");
			//SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}
	});
	ST->SetTransition("Duck", Input{  }, [anim, ST, RunningQueue](void) {
		//Do Nothing
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		AnimatorHolder::MarkAsSuspended(anim->at("Blocklow"));

	});
	ST->SetTransition("Duck", Input{ "o" }, [anim, ST, RunningQueue](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		AnimatorHolder::MarkAsSuspended(anim->at("Duck"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Blocklow"));
			canDoActionP2 = true;
			ST->SetState("Blocklow");
			//SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}

	});
	ST->SetTransition("Blocklow", Input{ }, [anim, ST, RunningQueue](void) {
		//Do Nothing
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));

	});
	ST->SetTransition("Blocklow", Input{ "1243" }, [anim, ST, RunningQueue](void) {
		//Do Nothing

	});
	ST->SetTransition("Idle", Input{ "o" }, [anim, ST, RunningQueue](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Blockhigh"));
			canDoActionP2 = false;
			//SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}

	});

	ST->SetTransition("Punchrighthigh", Input{ "7.7" }, [anim, ST, RunningQueue, thisFighter, opposingFighter](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Punchlefthigh"));
			canDoActionP2 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00214.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmghigh"));
			thisFighter->DamageOpponent(3, animeQueue);
		}

	});
	ST->SetTransition("Idle", Input{ "l.9" }, [anim, ST, RunningQueue, thisFighter, opposingFighter](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Kickround"));
			canDoActionP2 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmghigh"));
			thisFighter->DamageOpponent(3, animeQueue);
		}
	});
	ST->SetTransition("Idle", Input{ "l.8" }, [anim, ST, RunningQueue, thisFighter, opposingFighter](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			RunningQueue->push(anim->at("Tackle"));
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Getup"));
			animeQueue.push(opposingFighter->GetAnimators()->at("Fallside"));
			thisFighter->DamageOpponent(4, animeQueue);
			canDoActionP2 = false;
		}

	});
	ST->SetTransition("Idle", Input{ "k.7" }, [anim, ST, RunningQueue, thisFighter, opposingFighter](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Uppercut"));
			canDoActionP2 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00208.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Getup"));
			if (thisFighter->isFlipped)
				animeQueue.push(opposingFighter->GetAnimators()->at("FallbackMove"));
			else
				animeQueue.push(opposingFighter->GetAnimators()->at("FallbackRMove"));

			animeQueue.push(opposingFighter->GetAnimators()->at("Fallback"));
			thisFighter->DamageOpponent(4, animeQueue);
		}
	});
	ST->SetTransition("Idle", Input{ "9" }, [anim, ST, RunningQueue, thisFighter, opposingFighter](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Kickhigh"));
			canDoActionP2 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00213.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmghigh"));
			thisFighter->DamageOpponent(4, animeQueue);
		}
	});
	ST->SetTransition("Idle", Input{ "8" }, [anim, ST, RunningQueue, thisFighter, opposingFighter](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Kickmid"));
			canDoActionP2 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00213.mp3", false);
			queue<Animator*> animeQueue;
			animeQueue.push(opposingFighter->GetAnimators()->at("Dmgmid"));
			thisFighter->DamageOpponent(4, animeQueue);
		}
	});
	ST->SetTransition("Duck", Input{ "k.j.8" }, [anim, ST, RunningQueue](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Freezeball"));
			canDoActionP2 = false;
			//SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00208.mp3", false);
		}
	});
	ST->SetTransition("Idle", Input{ "j.9" }, [anim, ST, RunningQueue, currAnim](void) {
		if (canDoActionP2 && currAnim == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue->push(anim->at("Throw"));
			//canDoAction = false;
			ST->SetState("Throw");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00193.mp3", false);

		}
	});
	ST->SetTransition("Idle", Input{ "l.k.0" }, [anim, ST, RunningQueue, currAnim](void) {
		if (canDoActionP2 && currAnim == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue->push(anim->at("Kickslide"));
			//canDoAction = false;
			ST->SetState("Kickslide");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00193.mp3", false);

		}
	});
}

void Fighter::InitializeKeyCombinations()
{
	if (FighterName[playerIndex] == "Scorpion")
	{
		input::key_combination Duck;
		Duck.push_back("s");
		inputController.AddAction(Duck, "Duck");

		input::key_combination Blocklow;
		Blocklow.push_back("q");
		inputController.AddAction(Blocklow, "Blocklow");

		input::key_combination Blockhigh;
		Blockhigh.push_back("q");
		inputController.AddAction(Blockhigh, "Blockhigh");

		input::key_combination JumpForth;
		JumpForth.push_back("d");
		JumpForth.push_back("w");
		inputController.AddAction(JumpForth, "JumpForth");

		input::key_combination moveForward;
		moveForward.push_back("d");
		inputController.AddAction(moveForward, "moveforward");

		input::key_combination moveBackward;
		moveBackward.push_back("a");
		inputController.AddAction(moveBackward, "movebackward");

		input::key_combination punchrighthigh;
		punchrighthigh.push_back("4");
		inputController.AddAction(punchrighthigh, "punchrighthigh");

		input::key_combination punchlefthigh;
		punchlefthigh.push_back("4");
		punchlefthigh.push_back("4");
		inputController.AddAction(punchlefthigh, "punchlefthigh");

		input::key_combination punchrightmid;
		punchrightmid.push_back("3");
		inputController.AddAction(punchrightmid, "punchrightmid");

		input::key_combination punchleftmid;
		punchleftmid.push_back("3");
		punchleftmid.push_back("3");
		inputController.AddAction(punchleftmid, "punchleftmid");

		input::key_combination kickhigh;
		kickhigh.push_back("6");
		inputController.AddAction(kickhigh, "kickhigh");

		input::key_combination kickmid;
		kickmid.push_back("5");
		inputController.AddAction(kickmid, "kickmid");

		input::key_combination Throw;
		Throw.push_back("d");
		Throw.push_back("5");
		inputController.AddAction(Throw, "Throw");

		input::key_combination kickround;
		kickround.push_back("a");
		kickround.push_back("6");
		inputController.AddAction(kickround, "kickround");

		input::key_combination Uppercut;
		Uppercut.push_back("s");
		Uppercut.push_back("4");
		inputController.AddAction(Uppercut, "Uppercut");

		input::key_combination tackle;
		tackle.push_back("a");
		tackle.push_back("5");
		inputController.AddAction(tackle, "tackle");

		input::key_combination Rope;
		Rope.push_back("a");
		Rope.push_back("a");
		Rope.push_back("3");
		inputController.AddAction(Rope, "Rope");

		input::key_combination Fatality;
		Fatality.push_back("w");
		Fatality.push_back("w");
		inputController.AddAction(Fatality, "Fatality");

		input::key_combination jump;
		jump.push_back("w");
		inputController.AddAction(jump, "jump");

		input::key_combination jumppunch;
		jumppunch.push_back("w");
		jumppunch.push_back("3");
		inputController.AddAction(jumppunch, "jumppunch");
	}
	else if (FighterName[playerIndex] == "SubZero")
	{
		input::key_combination Duck;
		Duck.push_back("k");
		inputController.AddAction(Duck, "Duck");

		input::key_combination Blocklow;
		Blocklow.push_back("o");
		inputController.AddAction(Blocklow, "Blocklow");

		input::key_combination BlockHigh;
		BlockHigh.push_back("o");
		inputController.AddAction(BlockHigh, "BlockHigh");

		input::key_combination JumpForth;
		JumpForth.push_back("j");
		JumpForth.push_back("i");
		inputController.AddAction(JumpForth, "JumpForth");

		input::key_combination moveForward;
		moveForward.push_back("j");
		inputController.AddAction(moveForward, "moveforward");

		input::key_combination moveBackward;
		moveBackward.push_back("l");
		inputController.AddAction(moveBackward, "moveBackward");

		input::key_combination highpunch1;
		highpunch1.push_back("8");
		inputController.AddAction(highpunch1, "highpunch1");

		input::key_combination highpunch2;
		highpunch2.push_back("8");
		highpunch2.push_back("8");
		inputController.AddAction(highpunch2, "highpunch2");

		input::key_combination midpunch1;
		midpunch1.push_back("7");
		inputController.AddAction(midpunch1, "midpunch1");

		input::key_combination midpunch2;
		midpunch2.push_back("7");
		midpunch2.push_back("7");
		inputController.AddAction(midpunch2, "midpunch2");

		input::key_combination kickhigh;
		kickhigh.push_back("0");
		inputController.AddAction(kickhigh, "kickhigh");

		input::key_combination Kickmid;
		Kickmid.push_back("9");
		inputController.AddAction(Kickmid, "Kickmid");

		input::key_combination tackle;
		tackle.push_back("l");
		tackle.push_back("9");
		inputController.AddAction(tackle, "tackle");

		input::key_combination Throw;
		Throw.push_back("j");
		Throw.push_back("9");
		inputController.AddAction(Throw, "Throw");

		input::key_combination kickround;
		kickround.push_back("l");
		kickround.push_back("0");
		inputController.AddAction(kickround, "kickround");

		input::key_combination Uppercut;
		Uppercut.push_back("k");
		Uppercut.push_back("8");
		inputController.AddAction(Uppercut, "Uppercut");

		input::key_combination jump;
		jump.push_back("i");
		inputController.AddAction(jump, "jump");

		input::key_combination jumppunch;
		jumppunch.push_back("i");
		jumppunch.push_back("7");
		inputController.AddAction(jumppunch, "jumppunch");

		input::key_combination kickslide;
		kickslide.push_back("l");
		kickslide.push_back("k");
		kickslide.push_back("0");
		inputController.AddAction(kickslide, "kickslide");

		input::key_combination Freezeball;
		Freezeball.push_back("k");
		Freezeball.push_back("j");
		Freezeball.push_back("8");
		inputController.AddAction(Freezeball, "Freezeball");
	}

}

extern bool input::test_key(std::string keyCode, key_combination buttons) {
	int pressed = 0;
	for (auto item : buttons) {
		if (item == keyCode) {
			return true;
		}
	}
	return false;
}