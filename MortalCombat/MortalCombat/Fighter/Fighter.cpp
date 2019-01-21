#include "Fighter.h"
#include "../SoundEngine/SoundEngine.h"
#include <algorithm>
#include <future>
#include <queue>

Direction direction = Direction::none;
SDL_Joystick *joystick;

float timer = 0;

int Fighter::index = 0;
std::queue<Animator*> RunningQueue;
Animator* currAnimator;
bool canDoAction = true;

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
	
	InitializeStateMachine(&stateTransitions);
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

	UpdateKeys();
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
		}
		if (currAnimator->GetState() == ANIMATOR_FINISHED)
		{
			AnimatorHolder::MarkAsSuspended(currAnimator);
			currAnimator = NULL;
		}
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
						//if (!kayPressed[_event.key.keysym.sym])
						{
							//inputController.buttons.push_back("d");
							kayPressed[SDLK_d] = true;

						}
					}
					else if (_event.key.keysym.sym == SDLK_a) {
						direction = Direction::left;
						kayPressed[SDLK_a] = true;

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

void Fighter::InitializeStateMachine(logic::StateTransitions* ST) {
	ST->SetState("Idle");
	Animators* anim = animators;
	bool* flip = &rightIsForward;
	using Input = logic::StateTransitions::Input;
	int* player = &playerIndex;
	ST->SetTransition("Idle", Input{ }, [anim, ST](void) {
		if (currAnimator == NULL) {
			AnimatorHolder::MarkAsRunning(anim->at("Idle"));
			AnimatorHolder::MarkAsSuspended(anim->at("Punchrighthigh"));
			AnimatorHolder::MarkAsSuspended(anim->at("Punchlefthigh"));
			canDoAction = true;
		}
		//RunningQueue.push(anim->at("Idle"));
	});
	ST->SetTransition("Idle", Input{ "4" }, [anim, ST](void) {
		if (canDoAction && currAnimator == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue.push(anim->at("Punchrighthigh"));
			//canDoAction = false;
			ST->SetState("Punchrighthigh");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);

		}

	});
	ST->SetTransition("Punchrighthigh", Input{ "4.4" }, [anim, ST](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoAction) {
			RunningQueue.push(anim->at("Punchlefthigh"));
			canDoAction = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00199.mp3", false);
		}

	});
	ST->SetTransition("Idle", Input{ "5" }, [anim, ST](void) {
		if (canDoAction && currAnimator == NULL)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			if (ST->GetState() == "Idle")
				RunningQueue.push(anim->at("Kickmid"));
			//canDoAction = false;
			ST->SetState("Kickmid");
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00193.mp3", false);

		}
	});
	ST->SetTransition("Kickmid", Input{ "5.5" }, [anim, ST](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoAction) {
			RunningQueue.push(anim->at("Kickhigh"));
			canDoAction = false;
		}

	});
	ST->SetTransition("Idle", Input{ "a.6" }, [anim, ST](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoAction) {
			RunningQueue.push(anim->at("Kickround"));
			canDoAction = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00193.mp3", false);

		}

	});

	ST->SetTransition("Idle", Input{ "s.4" }, [anim, ST](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoAction) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			RunningQueue.push(anim->at("Uppercut"));
			canDoAction = false;
			SoundEngine::Get()->Play("SoundEngine/Sounds/male/mk1-00208.mp3", false);

		}

	});
	ST->SetTransition("Idle", Input{ "a.5" }, [anim, ST](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoAction) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			RunningQueue.push(anim->at("Tackle"));
			canDoAction = false;
		}

	});
	ST->SetTransition("Idle", Input{ "w.w" }, [anim, ST](void) {
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		if (canDoAction) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			RunningQueue.push(anim->at("Burn"));
			canDoAction = false;
		}

	});
	ST->SetTransition("Idle", Input{ "d" }, [anim, ST](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		ST->SetState("Walk");
	});
	ST->SetTransition("Walk", Input{ }, [anim, ST, flip, player](void) {
		if (*player == P1)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("WalkR"));
			AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseR"));
		}
		ST->SetState("Idle");
	});
	ST->SetTransition("Idle", Input{ "a" }, [anim, ST](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		ST->SetState("WalkRev");
	});
	ST->SetTransition("WalkRev", Input{ }, [anim, ST, player, flip](void) {
		if (*player == P1)
		{
			AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseL"));
			AnimatorHolder::MarkAsSuspended(anim->at("WalkL"));
		}
		ST->SetState("Idle");
	});
	ST->SetTransition("Walk", playerIndex == P1 ? Input{ "d" } : Input{ "j" }, [anim, ST, flip, player](void) {
		if (*player == P1)
		{
			if (*flip) {

				AnimatorHolder::MarkAsRunning(anim->at("WalkR"));
				AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseR"));
			}
			else {
				AnimatorHolder::MarkAsSuspended(anim->at("WalkR"));
				AnimatorHolder::MarkAsRunning(anim->at("WalkReverseR"));
			}
		}
	});
	ST->SetTransition("Walk", playerIndex == P1 ? Input{ "d.5" } : Input{ "j" }, [anim, ST](void) {
		if (canDoAction) {
			AnimatorHolder::MarkAsSuspended(anim->at("Walk"));
			RunningQueue.push(anim->at("Throw"));
			canDoAction = false;
		}	});
	ST->SetTransition("WalkRev", playerIndex == P1 ? Input{ "a" } : Input{ "l" }, [anim, ST, flip, player](void) {
		if (*player == P1)
		{
			if (*flip) {
				AnimatorHolder::MarkAsSuspended(anim->at("WalkL"));
				AnimatorHolder::MarkAsRunning(anim->at("WalkReverseL"));
			}
			else {
				AnimatorHolder::MarkAsSuspended(anim->at("WalkReverseL"));
				AnimatorHolder::MarkAsRunning(anim->at("WalkL"));
			}
		}
	});
	ST->SetTransition("Idle", playerIndex == P1 ? Input{ "a.a.3" } : Input{ "l" }, [anim, ST](void) {
		if (canDoAction) {
			AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
			RunningQueue.push(anim->at("Rope"));
			canDoAction = false;
			int r = rand() % 2;
			if (r == 0)
				SoundEngine::Get()->Play("SoundEngine/Sounds/scorpion/mk1-goh.mp3", false);
			else {
				SoundEngine::Get()->Play("SoundEngine/Sounds/scorpion/mk1-00446.mp3", false);
			}

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
	}
	else if (FighterName[playerIndex] == "SubZero") {
		//TODO: add subzero keys here
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