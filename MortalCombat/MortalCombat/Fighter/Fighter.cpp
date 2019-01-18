#include "Fighter.h"
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
	AnimatorHolder::MarkAsRunning(animators->at("Idle"));

	Renderer = renderer;

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
		//s->SetAnimFilm(afh->GetFilm("Idle"));
		AnimatorHolder::MarkAsSuspended(anim->at("Walk"));
		AnimatorHolder::MarkAsSuspended(anim->at("WalkReverse"));
		AnimatorHolder::MarkAsSuspended(anim->at("Punchrighthigh"));
		AnimatorHolder::MarkAsSuspended(anim->at("Punchlefthigh"));
		AnimatorHolder::MarkAsRunning(anim->at("Idle"));
	});
	stateTransitions.SetTransition("Idle", playerIndex == P1 ? Input{ "d" } : Input{ "j" }, [s, afh, anim](void) {
		//s->SetAnimFilm(afh->GetFilm("Walk"));

		AnimatorHolder::MarkAsSuspended(anim->at("Punchrighthigh"));
		AnimatorHolder::MarkAsSuspended(anim->at("WalkReverse"));
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		AnimatorHolder::MarkAsSuspended(anim->at("Punchlefthigh"));
		AnimatorHolder::MarkAsRunning(anim->at("Walk"));
		
	});
	stateTransitions.SetTransition("Idle", playerIndex == P1 ? Input{ "a" } : Input{ "l" }, [s, afh, anim](void) {
		//s->SetAnimFilm(afh->GetFilm("Walk"), true);
		AnimatorHolder::MarkAsSuspended(anim->at("Punchrighthigh"));
		AnimatorHolder::MarkAsSuspended(anim->at("Walk"));
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		AnimatorHolder::MarkAsSuspended(anim->at("Punchlefthigh"));
		AnimatorHolder::MarkAsRunning(anim->at("WalkReverse"));

	});
	stateTransitions.SetTransition("Idle", playerIndex == P1 ? Input{ "4" } : Input{ "8" }, [s, afh, anim, state](void) {
		//s->SetAnimFilm(afh->GetFilm("Punchrighthigh"));
		AnimatorHolder::MarkAsSuspended(anim->at("Walk"));
		AnimatorHolder::MarkAsSuspended(anim->at("WalkReverse"));
		AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		AnimatorHolder::MarkAsSuspended(anim->at("Punchlefthigh"));
		AnimatorHolder::MarkAsRunning(anim->at("Punchrighthigh"));
		state->SetState("HighPunch1");


	});
	stateTransitions.SetTransition("HighPunch1", playerIndex == P1 ? Input{ "4" } : Input{ "8" }, [s, afh, anim, state](void) {
		//s->SetAnimFilm(afh->GetFilm("Punchlefthigh"));
		//AnimatorHolder::MarkAsSuspended(anim->at("Walk"));
		//AnimatorHolder::MarkAsSuspended(anim->at("WalkReverse"));
		//AnimatorHolder::MarkAsSuspended(anim->at("Idle"));
		AnimatorHolder::MarkAsSuspended(anim->at("Punchrighthigh"));
		AnimatorHolder::MarkAsRunning(anim->at("Punchlefthigh"));
		//state->SetState("Idle");

	});
	stateTransitions.SetTransition("HighPunch1", Input{  }, [s, afh, anim, state](void) {
		state->SetState("Idle");
	});
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

float Fighter::GetHealth()
{
	return health;
}

void Fighter::Update()
{
	AnimationFilmHolder& AFH = AnimationFilmHolder::Get();

	UpdateKeys();
	inputController.Handle();
	bool isActionRunning = false;
	bool isMovementRunning = false;
	bool isIdleRunning = false;
	

	stateTransitions.PerformTransitions(inputController.buttons, false);

	AnimatorHolder::Progress(float((float)clock() / (float)CLOCKS_PER_SEC));
	AnimatorHolder::Render(Renderer);
}

void Fighter::UpdateKeys() {
	SDL_Event _event;
	SDL_PollEvent(&_event);
	switch (_event.type)
	{
		case SDL_KEYDOWN: {
			if (_event.key.state == SDL_PRESSED)
			{
				if (playerIndex == P1)
				{
					if (_event.key.keysym.sym == SDLK_d) {
						direction = Direction::right;
						inputController.buttons.push_back("d");

					}
					else if (_event.key.keysym.sym == SDLK_a) {
						direction = Direction::left;
						inputController.buttons.push_back("a");

					}
					else if (_event.key.keysym.sym == SDLK_4) {
						inputController.buttons.push_back("4");

					}
					else if (_event.key.keysym.sym == SDLK_5) {
						inputController.buttons.push_back("5");

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
				if (_event.key.keysym.sym == SDLK_d || _event.key.keysym.sym == SDLK_a) {
					direction = Direction::none;
				}
				return;
			}
			break;
		}
	}
	if (float((float)clock() / (float)CLOCKS_PER_SEC) - timer > (float) ((float) FIGHTER_ACTION_DELAY_MSECS / 1000.0f)) {
		
		int k = 0;
		for (auto i : inputController.buttons) {
			std::cout << i << " - ";
			if (k == inputController.buttons.size() - 1)
				std::cout << std::endl;
			k++;
		}

		inputController.buttons.clear();

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