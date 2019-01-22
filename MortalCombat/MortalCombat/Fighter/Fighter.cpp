#include "Fighter.h"
#include "../SoundEngine/SoundEngine.h"
#include <algorithm>
#include <future>

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

	using Input = logic::StateTransitions::Input;
	
	AnimationFilmHolder& AFH = AnimationFilmHolder::Get();
	tag = _tag;
	health = 100.0;
	isAlive = true;

	this->playerIndex = playerIndex;

	InitializeCharacter(_tag, renderer);

	std::string forward = rightIsForward ? "d" : "a";
	//sprite->SetAnimFilm(AFH.GetFilm("Idle"));
	//AnimatorHolder::MarkAsRunning(animators->at("Idle"));

	Renderer = renderer;

	InitializeKeyCombinations();

	stateTransitions.SetState("Idle");

	Sprite* s = sprite;
	AnimationFilmHolder* afh = &AFH;
	Animators* anim = animators;
	
	logic::StateTransitions *state = &stateTransitions;
	
	if (playerIndex == 0)
		InitializeStateMachineScorpion(&stateTransitions);
	else
		InitializeStateMachineSubZero(&stateTransitions);

}

bool Fighter::PlayerIsAlive()
{
	return isAlive;
}

void Fighter::DamagePlayer(int damage)
{
	health -= damage;
	
	//Set health back to zero to avoid visual bugs (lifebar)


	if (health < 0)
		health = 0;
}
Fighter::Fighter()
{
}
int Fighter::GetHealth()
{
	return health;
}

void Fighter::Update()
{
	using Input = logic::StateTransitions::Input;

	AnimationFilmHolder& AFH = AnimationFilmHolder::Get();

	//UpdateKeys();
	if (direction == left) {
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
	else if (direction == right) {
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

		std::cout << str << std::endl;
	}
	if (y <= 220) {
		y += 2;
	}
	else if (y <= 280) {
		y += 5;
	}
	else if (y < 330) {
		y += 7;
	}
	else if (y > 330) {
		y = 330;
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

}
bool kayPressed[500000];
void Fighter::UpdateKeys() {
	SDL_Event _event;
	while(SDL_PollEvent(&_event))
	switch (_event.type)
	{
		case SDL_KEYDOWN: {
			if (_event.key.state == SDL_PRESSED)
			{

				if (playerIndex == P1)
				{
					if (_event.key.keysym.sym == SDLK_d ) {
						direction = Direction::right;
						if (!kayPressed[_event.key.keysym.sym])
						{
							//inputController.buttons.push_back("d");
							kayPressed[SDLK_d] = true;
							inputController.buttons.push_back("d");
						}
					}
					else if (_event.key.keysym.sym == SDLK_a) {
						if (!kayPressed[SDLK_a]) {
							direction = Direction::left;
							kayPressed[SDLK_a] = true;
							inputController.buttons.push_back("a");
						}
					}
					else if (_event.key.keysym.sym == SDLK_3) {
						if (!kayPressed[_event.key.keysym.sym])
						{
							inputController.buttons.push_back("3");
							kayPressed[_event.key.keysym.sym] = true;
						}
					}
					else if (_event.key.keysym.sym == SDLK_4) {
						if (!kayPressed[_event.key.keysym.sym])
						{
							inputController.buttons.push_back("4");
							kayPressed[_event.key.keysym.sym] = true;
						}
					}
					else if (_event.key.keysym.sym == SDLK_5) {
						if (!kayPressed[_event.key.keysym.sym])
						{
							inputController.buttons.push_back("5");
							kayPressed[_event.key.keysym.sym] = true;
						}
					}
					else if (_event.key.keysym.sym == SDLK_w) {
						if (!kayPressed[_event.key.keysym.sym])
						{
							inputController.buttons.push_back("w");
							kayPressed[_event.key.keysym.sym] = true;
						}
					}
					else if (_event.key.keysym.sym == SDLK_6) {
						if (!kayPressed[SDLK_6])
						{
							inputController.buttons.push_back("6");
							kayPressed[SDLK_6] = true;
						}
					}
					else if (_event.key.keysym.sym == SDLK_s) {
						if (!kayPressed[_event.key.keysym.sym])
						{
							inputController.buttons.push_back("s");
							kayPressed[_event.key.keysym.sym] = true;
						}
					}

				}
				else
				{
					if (_event.key.keysym.sym == SDLK_j) {
						direction = Direction::left;
						inputController.buttons.push_back("j");

					}
					else if (_event.key.keysym.sym == SDLK_l) {
						direction = Direction::left;
						inputController.buttons.push_back("l");

					}
					else if (_event.key.keysym.sym == SDLK_8) {
						inputController.buttons.push_back("8");

					}
					else if (_event.key.keysym.sym == SDLK_9) {
						inputController.buttons.push_back("9");

					}
				}
				
				timer = float((float)clock() / (float)CLOCKS_PER_SEC);
				return;
			}	
			break;
		}
		case SDL_KEYUP: {
			if (_event.key.state == SDL_RELEASED)
			{
				if (_event.key.keysym.sym < 500000) {
					kayPressed[_event.key.keysym.sym] = false;					
				}
				return;
			}
			break;
		}
		case SDL_JOYBUTTONDOWN: {
			std::cout << (int)_event.jbutton.button;
			if ((int)_event.jbutton.button == SDL_CONTROLLER_BUTTON_X) {
				if (!kayPressed[SDLK_6])
				{
					inputController.buttons.push_back("6");
					kayPressed[SDLK_6] = true;
				}
			}
			if ((int)_event.jbutton.button == SDL_CONTROLLER_BUTTON_A) {
				if (!kayPressed[SDLK_5])
				{
					inputController.buttons.push_back("5");
					kayPressed[SDLK_5] = true;
				}
			}
			if ((int)_event.jbutton.button == SDL_CONTROLLER_BUTTON_Y) {
				if (!kayPressed[SDLK_4])
				{
					inputController.buttons.push_back("4");
					kayPressed[SDLK_4] = true;
				}
			}
			if ((int)_event.jbutton.button == SDL_CONTROLLER_BUTTON_B) {
				if (!kayPressed[SDLK_3])
				{
					inputController.buttons.push_back("3");
					kayPressed[SDLK_3] = true;
				}
			}
			timer = float((float)clock() / (float)CLOCKS_PER_SEC);

		}
		case SDL_JOYBUTTONUP: {
			if ((int)_event.jbutton.button == SDL_CONTROLLER_BUTTON_X) {
				{
					kayPressed[SDLK_6] = false;
				}
			}
			if ((int)_event.jbutton.button == SDL_CONTROLLER_BUTTON_A) {
				{
					kayPressed[SDLK_5] = false;
				}
			}
			if ((int)_event.jbutton.button == SDL_CONTROLLER_BUTTON_Y) {
				{
					kayPressed[SDLK_4] = false;
				}
			}
			if ((int)_event.jbutton.button == SDL_CONTROLLER_BUTTON_B) {
				{
					kayPressed[SDLK_3] = false;
				}
			}
			
		}
		case SDL_JOYHATMOTION: {
			timer = float((float)clock() / (float)CLOCKS_PER_SEC);

			if ((int)_event.jhat.value == SDL_HAT_LEFT) {
				if (!kayPressed[SDLK_a])
				{
					inputController.buttons.push_back("a");
					kayPressed[SDLK_a] = true;
				}
			}
			if ((int)_event.jhat.value == SDL_HAT_RIGHT) {
				if (!kayPressed[SDLK_d])
				{
					inputController.buttons.push_back("d");
					kayPressed[SDLK_d] = true;
				}
			}
			if ((int)_event.jhat.value == SDL_HAT_DOWN) {
				if (!kayPressed[SDLK_s])
				{
					inputController.buttons.push_back("s");
					kayPressed[SDLK_s] = true;
				}
			}
			//if ((int)_event.jhat.hat == SDL_HAT_UP) {
			//	if (!kayPressed[SDLK_w])
			//	{
			//		inputController.buttons.push_back("w");
			//		kayPressed[SDLK_w] = true;
			//	}
			//}
			if ((int)_event.jhat.value == SDL_HAT_CENTERED) {
				kayPressed[SDLK_d] = false;
				kayPressed[SDLK_a] = false;
				kayPressed[SDLK_s] = false;
				kayPressed[SDLK_w] = false;
			}
		}
	}
	if (float((float)clock() / (float)CLOCKS_PER_SEC) - timer > (float) ((float) FIGHTER_ACTION_DELAY_MSECS / 1000.0f)) {


		inputController.buttons.clear();
		if (kayPressed[SDLK_a]) {
			inputController.buttons.push_back("a");
		}
		if (kayPressed[SDLK_d]) {
			inputController.buttons.push_back("d");
		}
		
	}
	
	//if (kayPressed[SDLK_4]) {
	//	inputController.buttons.push_back("4");
	//}
}

void Fighter::InitializeStateMachineScorpion(logic::StateTransitions* ST) {
	ST->SetState("Idle");
	Animators* anim = animators;
	bool* flip = &rightIsForward;
	using Input = logic::StateTransitions::Input;
	int* player = &playerIndex;
	std::queue<Animator*> *RunningQueue = &this->RunningQueue;
	std::queue<Animator*> *MovingQueue = &this->MovingQueue;;
	Animator* currAnim = currAnimator;
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
	ST->SetTransition("Jump", Input{ "5" }, [anim, ST, currAnim](void) {
		if (currAnim == NULL) {
			
		}
		//RunningQueue.push(anim->at("Idle"));
	});
	ST->SetTransition("Idle", Input{ "4" }, [anim, ST, RunningQueue, currAnim](void) {
		if (canDoActionP1 && currAnim == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue->push(anim->at("Punchrighthigh"));
			//canDoAction = false;
			ST->SetState("Punchrighthigh");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);

		}

	});
	ST->SetTransition("Punchrighthigh", Input{ "4.4" }, [anim, ST, RunningQueue](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			RunningQueue->push(anim->at("Punchlefthigh"));
			canDoActionP1 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}

	});
	ST->SetTransition("Idle", Input{ "5" }, [anim, ST, RunningQueue, currAnim](void) {
		if (canDoActionP1 && currAnim == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue->push(anim->at("Kickmid"));
			//canDoAction = false;
			ST->SetState("Kickmid");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00193.mp3", false);

		}
	});
	ST->SetTransition("Kickmid", Input{ "5.5" }, [anim, ST, RunningQueue](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			RunningQueue->push(anim->at("Kickhigh"));
			canDoActionP1 = false;
		}

	});
	ST->SetTransition("Idle", Input{ "a.6" }, [anim, ST, RunningQueue](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			RunningQueue->push(anim->at("Kickround"));
			canDoActionP1 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00193.mp3", false);
		}

	});

	ST->SetTransition("Idle", Input{ "s.4" }, [anim, ST, RunningQueue](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			RunningQueue->push(anim->at("Uppercut"));
			canDoActionP1 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00208.mp3", false);

		}

	});
	ST->SetTransition("Idle", Input{ "a.5" }, [anim, ST, RunningQueue](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			RunningQueue->push(anim->at("Tackle"));
			canDoActionP1 = false;
		}

	});
	ST->SetTransition("Idle", Input{ "w.w" }, [anim, ST, RunningQueue](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP1) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
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

	ST->SetTransition("Idle", Input{ }, [anim, ST](void) {
		canDoActionP2 = true;
	});
	ST->SetTransition("Idle", Input{ "7" }, [anim, ST, RunningQueue, currAnim](void) {
		if (canDoActionP2 && currAnim == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue->push(anim->at("Punchrighthigh"));
			//canDoAction = false;
			ST->SetState("Punchrighthigh");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);

		}

	});
	ST->SetTransition("Punchrighthigh", Input{ "7.7" }, [anim, ST, RunningQueue](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Punchlefthigh"));
			canDoActionP2 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}

	});
	ST->SetTransition("Idle", Input{ "j.9" }, [anim, ST, RunningQueue](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Kickround"));
			canDoActionP2 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}
	});
	ST->SetTransition("Idle", Input{ "k.7" }, [anim, ST, RunningQueue](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Uppercut"));
			canDoActionP2 = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00208.mp3", false);
		}
	});
	ST->SetTransition("Idle", Input{ "9" }, [anim, ST, RunningQueue](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Kickhigh"));
			canDoActionP2 = false;
			//SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00208.mp3", false);
		}
	});
	ST->SetTransition("Idle", Input{ "8" }, [anim, ST, RunningQueue](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoActionP2) {
			RunningQueue->push(anim->at("Kickmid"));
			canDoActionP2 = false;
			//SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00208.mp3", false);
		}
	});
}

void Fighter::InitializeKeyCombinations()
{
	if (FighterName[playerIndex] == "Scorpion") {
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

		input::key_combination kickhigh;
		kickhigh.push_back("5");
		inputController.AddAction(kickhigh, "kickhigh");

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

		input::key_combination Throw;
		Throw.push_back("d");
		Throw.push_back("5");
		inputController.AddAction(Throw, "tackle");

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
	}
	else if (FighterName[playerIndex] == "SubZero") {
		input::key_combination moveForward;
		moveForward.push_back("j");
		inputController.AddAction(moveForward, "moveforward");

		input::key_combination moveBackward;
		moveBackward.push_back("l");
		inputController.AddAction(moveBackward, "moveBackward");

		input::key_combination highpunch1;
		highpunch1.push_back("7");
		inputController.AddAction(highpunch1, "highpunch1");

		input::key_combination highpunch2;
		highpunch2.push_back("7");
		highpunch2.push_back("7");
		inputController.AddAction(highpunch2, "highpunch2");

		input::key_combination kickhigh;
		kickhigh.push_back("9");
		inputController.AddAction(kickhigh, "kickhigh");

		input::key_combination Kickmid;
		Kickmid.push_back("8");
		inputController.AddAction(Kickmid, "Kickmid");

		input::key_combination kickround;
		kickround.push_back("j");
		kickround.push_back("9");
		inputController.AddAction(kickround, "kickround");

		input::key_combination Uppercut;
		Uppercut.push_back("k");
		Uppercut.push_back("7");
		inputController.AddAction(Uppercut, "Uppercut");
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