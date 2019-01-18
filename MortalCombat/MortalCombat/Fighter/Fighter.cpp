#include "Fighter.h"
#include <algorithm>
#include <future>

Direction direction = Direction::none;

float timer = 0;

Fighter::Fighter(FighterTag _tag, int playerIndex, SDL_Renderer *renderer)
{
	using Input = logic::StateTransitions::Input;
	
	AnimationFilmHolder& AFH = AnimationFilmHolder::Get();
	tag = _tag;
	health = 100.0;
	isAlive = true;

	this->playerIndex = playerIndex;

	InitializeCharacter(_tag, renderer);


	//sprite->SetAnimFilm(AFH.GetFilm("Idle"));
	//AnimatorHolder::MarkAsRunning(animators->at("Idle"));

	Renderer = renderer;

	input::key_combination test;
	test.push_back("4");
	test.push_back("4");
	test.push_back("4");
	inputController.AddAction(test, "test");

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

	stateTransitions.SetState("Idle");

	Sprite* s = sprite;
	AnimationFilmHolder* afh = &AFH;
	Animators* anim = animators;
	
	logic::StateTransitions *state = &stateTransitions;
	state->SetState("Idle");

	stateTransitions.SetTransition("Idle", Input{ }, [s, afh, anim, state](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Walk"));
		AnimatorHolder::MarkAsSuspended(anim->at("WalkReverse"));
		AnimatorHolder::MarkAsRunning(anim->at("Idle"));

	});
	stateTransitions.SetTransition("Idle", Input{ "4.4.4" }, [s, afh, anim, state](void) {
		std::cout << "MPIKA" << std::endl;

	});
	stateTransitions.SetTransition("Idle", Input{ "d" }, [s, afh, anim, state](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		state->SetState("Walk");
	});
	stateTransitions.SetTransition("Walk", Input{ }, [s, afh, anim, state](void) {
		state->SetState("Idle");
	});
	stateTransitions.SetTransition("Idle", Input{ "a" }, [s, afh, anim, state](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		state->SetState("WalkRev");
	});
	stateTransitions.SetTransition("WalkRev", Input{ }, [s, afh, anim, state](void) {
		state->SetState("Idle");
	});
	stateTransitions.SetTransition("Walk", playerIndex == P1 ? Input{ "d" } : Input{ "j" }, [s, afh, anim, state](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("WalkReverse"));
		AnimatorHolder::MarkAsRunning(anim->at("Walk"));
	});
	stateTransitions.SetTransition("WalkRev", playerIndex == P1 ? Input{ "a" } : Input{ "l" }, [s, afh, anim, state](void) {
		AnimatorHolder::MarkAsSuspended(anim->at("Walk"));
		AnimatorHolder::MarkAsRunning(anim->at("WalkReverse"));

	});

	//stateTransitions.SetTransition("Idle", playerIndex == P1 ? Input{ "4" } : Input{ "8" }, [s, afh, anim, state](void) {
	//	//s->SetAnimFilm(afh->GetFilm("Punchrighthigh"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("Walk"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("WalkReverse"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("Punchlefthigh"));
	//	AnimatorHolder::MarkAsRunning(anim->at("Punchrighthigh"));
	//	state->SetState("HighPunch1");


	//});
	//stateTransitions.SetTransition("HighPunch1", playerIndex == P1 ? Input{ "4" } : Input{ "8" }, [s, afh, anim, state](void) {
	//	//s->SetAnimFilm(afh->GetFilm("Punchlefthigh"));
	//	//AnimatorHolder::MarkAsSuspended(anim->at("Walk"));
	//	//AnimatorHolder::MarkAsSuspended(anim->at("WalkReverse"));
	//	//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("Punchrighthigh"));
	//	AnimatorHolder::MarkAsRunning(anim->at("Punchlefthigh"));
	//	//state->SetState("Idle");

	//});
	//stateTransitions.SetTransition("HighPunch1", Input{  }, [s, afh, anim, state](void) {
	//	state->SetState("Idle");
	//});
	//stateTransitions.SetTransition("Idle", Input{ "5" }, [s, afh, anim, state](void) {
	//	s->SetAnimFilm(afh->GetFilm("Kickmid"));
	//	AnimatorHolder::MarkAsRunning(anim->at("kickmid"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("walk"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("walkReverse"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("punchrighthigh"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("punchlefthigh"));
	//	state->SetState("kick1");

	//});
	//stateTransitions.SetTransition("kick1", Input{ "5" }, [s, afh, anim, state](void) {
	//	s->SetAnimFilm(afh->GetFilm("Kickhigh"));
	//	AnimatorHolder::MarkAsRunning(anim->at("kickhigh"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("kickmid"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("walk"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("walkReverse"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("punchrighthigh"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("punchlefthigh"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("idle"));
	//	//state->SetState("Idle");

	//});
	//stateTransitions.SetTransition("kick1", Input{  }, [s, afh, anim, state](void) {
	//	s->SetAnimFilm(afh->GetFilm("Idle"));
	//	AnimatorHolder::MarkAsRunning(anim->at("idle"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("walk"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("walkReverse"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("kickmid"));
	//	AnimatorHolder::MarkAsSuspended(anim->at("kickhigh"));
	//	state->SetState("Idle");

	//});

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

	AnimatorHolder::Progress(float((float)clock() / (float)CLOCKS_PER_SEC));
	AnimatorHolder::Render(Renderer);
}
bool kayPressed[500000];
void Fighter::UpdateKeys() {
	SDL_Event _event;
	while(SDL_PollEvent(&_event))
	switch (_event.key.state)
	{
		case SDL_PRESSED: {
			if (_event.key.state == SDL_PRESSED)
			{
				if (playerIndex == P1)
				{
					if (_event.key.keysym.sym == SDLK_d) {
						direction = Direction::right;
						//if (!kayPressed[_event.key.keysym.sym])
						{
							//inputController.buttons.push_back("d");
							kayPressed[_event.key.keysym.sym] = true;
						}
					}
					else if (_event.key.keysym.sym == SDLK_a) {
						direction = Direction::left;
						//if (kayPressed[_event.key.keysym.sym])
						{
							//inputController.buttons.push_back("a");
							kayPressed[_event.key.keysym.sym] = true;
						}
					}
					else if (_event.key.keysym.sym == SDLK_4) {
						//if (kayPressed[_event.key.keysym.sym])
						{
							inputController.buttons.push_back("4");
							kayPressed[_event.key.keysym.sym] = true;
						}
					}
					else if (_event.key.keysym.sym == SDLK_5) {
						if (kayPressed[_event.key.keysym.sym])
						{
							inputController.buttons.push_back("5");
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
		case SDL_RELEASED: {
			if (_event.key.state == SDL_RELEASED)
			{
				if (_event.key.keysym.sym == SDLK_d || _event.key.keysym.sym == SDLK_a) {
					direction = Direction::none;
				}
				if (_event.key.keysym.sym < 500000) {
					kayPressed[_event.key.keysym.sym] = false;
					
				}


				return;
			}
			break;
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

extern bool input::test_key(std::string keyCode, key_combination buttons) {
	int pressed = 0;
	for (auto item : buttons) {
		if (item == keyCode) {
			return true;
		}
	}
	return false;
}