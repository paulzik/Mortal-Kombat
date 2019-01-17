#include "Fighter.h"
#include <future>

Direction direction = Direction::none;

float timer = 0;

Fighter::Fighter(FighterTag _tag, SDL_Renderer *renderer)
{
	tag = _tag;
	health = 100.0;
	isAlive = true;

	InitializeCharacter(_tag, renderer);

	sprite->SetAnimFilm(AFH->GetFilm("Idle"));
	AnimatorHolder::MarkAsRunning(animators->at("idle"));

	Renderer = renderer;

	input::key_combination moveForward;
	moveForward.push_back(SDLK_d);
	inputController.AddAction(moveForward, "moveforward");

	input::key_combination moveBackward;
	moveBackward.push_back(SDLK_a);
	inputController.AddAction(moveBackward, "movebackward");

	input::key_combination punchrighthigh;
	punchrighthigh.push_back(SDLK_4);
	inputController.AddAction(punchrighthigh, "punchrighthigh");

	input::key_combination punchlefthigh;
	punchlefthigh.push_back(SDLK_4);
	punchlefthigh.push_back(SDLK_4);
	inputController.AddAction(punchlefthigh, "punchlefthigh");
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
	

	UpdateKeys();
	inputController.Handle();
	bool isActionRunning = false;
	bool isMovementRunning = false;
	bool isIdleRunning = false;
	for (auto anim : GetRunningAnimators()) {
		if (anim->GetState() == animatorstate_t::ANIMATOR_RUNNING && anim->GetType() == animatortype_t::action)
			isActionRunning = true;
		if (anim->GetState() == animatorstate_t::ANIMATOR_RUNNING && anim->GetType() == animatortype_t::movement)
			isMovementRunning = true;
		if (anim->GetState() == animatorstate_t::ANIMATOR_RUNNING && anim->GetType() == animatortype_t::movement)
			isIdleRunning = true;
	}
	if (!isIdleRunning && !isMovementRunning && !isActionRunning && inputController.buttons.size() == 0) {
		sprite->SetAnimFilm(AFH->GetFilm("Idle"));
		AnimatorHolder::MarkAsRunning(animators->at("idle"));
		AnimatorHolder::MarkAsSuspended(animators->at("walk"));
		AnimatorHolder::MarkAsSuspended(animators->at("walkReverse"));
	}

	for (auto item : inputController.GetLogical()) {
		if (item == "moveforward") {
			sprite->SetAnimFilm(AFH->GetFilm("Walk"));
			AnimatorHolder::MarkAsRunning(animators->at("walk"));
			AnimatorHolder::MarkAsSuspended(animators->at("walkReverse"));
			AnimatorHolder::MarkAsSuspended(animators->at("idle"));
		}
		else if (item == "movebackward") {
			sprite->SetAnimFilm(AFH->GetFilm("Walk"), true);
			AnimatorHolder::MarkAsRunning(animators->at("walkReverse"));
			AnimatorHolder::MarkAsSuspended(animators->at("walk"));
			AnimatorHolder::MarkAsSuspended(animators->at("idle"));

		}
		else if (item == "punchrighthigh") {
			
			sprite->SetAnimFilm(AFH->GetFilm("Punchrighthigh"));
			AnimatorHolder::MarkAsRunning(animators->at("punchrighthigh"));
			AnimatorHolder::MarkAsSuspended(animators->at("walk"));
			AnimatorHolder::MarkAsSuspended(animators->at("walkReverse"));
			AnimatorHolder::MarkAsSuspended(animators->at("idle"));
			AnimatorHolder::MarkAsSuspended(animators->at("punchlefthigh"));

		}
		else if (item == "punchlefthigh") {
				sprite->SetAnimFilm(AFH->GetFilm("Punchlefthigh"));
				AnimatorHolder::MarkAsRunning(animators->at("punchlefthigh"));
				AnimatorHolder::MarkAsSuspended(animators->at("walk"));
				AnimatorHolder::MarkAsSuspended(animators->at("walkReverse"));
				AnimatorHolder::MarkAsSuspended(animators->at("idle"));
				AnimatorHolder::MarkAsSuspended(animators->at("punchrighthigh"));
		}


	}
	

	AnimatorHolder::Progress(float((float)clock() / (float)CLOCKS_PER_SEC));
	AnimatorHolder::Render(Renderer);

	std::cout << isActionRunning << " " << isMovementRunning << " " << isIdleRunning << std::endl;

	
}

void Fighter::UpdateKeys() {
	SDL_Event _event;
	SDL_PollEvent(&_event);
	switch (_event.type)
	{
		case SDL_KEYDOWN: {
			if (_event.key.state == SDL_PRESSED)
			{
				if (_event.key.keysym.sym == SDLK_d) {
					direction = Direction::right;
				}
				else if (_event.key.keysym.sym == SDLK_a) {
					direction = Direction::left;
				}
				
				inputController.buttons.push_back(_event.key.keysym.sym);
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

extern bool input::test_key(int32_t keyCode, key_combination buttons) {
	int pressed = 0;
	for (auto item : buttons) {
		if (item == keyCode) {
			return true;
		}
	}
	return false;
}