#include "Fighter.h"
Direction direction = Direction::none;
std::list< int32_t > buttons;

float timer = 0;
void UpdateKeys();

Fighter::Fighter(FighterTag _tag, SDL_Renderer *renderer)
{
	AnimationFilmHolder& AFH = AnimationFilmHolder::Get();
	tag = _tag;
	health = 100.0;
	isAlive = true;

	InitializeCharacter(_tag, renderer);

	sprite->SetAnimFilm(AFH.GetFilm("Idle"));
	animator->MarkAsRunning(animators->at("idle"));

	Renderer = renderer;

	input::key_combination moveForward;
	moveForward.push_back(SDLK_d);
	inputController.AddAction(moveForward, "moveforward");

	input::key_combination moveBackward;
	moveBackward.push_back(SDLK_a);
	inputController.AddAction(moveBackward, "movebackward");
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

	for (auto item : inputController.GetLogical()) {
		if (item == "moveforward") {
			sprite->SetAnimFilm(AFH.GetFilm("Walk"));
			animator->MarkAsRunning(animators->at("walk"));
			animator->MarkAsSuspended(animators->at("walkReverse"));
			animator->MarkAsSuspended(animators->at("idle"));
		}
		else if (item == "movebackward") {
			sprite->SetAnimFilm(AFH.GetFilm("Walk"), true);
			animator->MarkAsRunning(animators->at("walkReverse"));
			animator->MarkAsSuspended(animators->at("walk"));
			animator->MarkAsSuspended(animators->at("idle"));

		}
	}




	animator->Progress(float((float)clock() / (float)CLOCKS_PER_SEC));
	animator->Render(Renderer);


	if (float((float)clock() / (float)CLOCKS_PER_SEC) - timer > ((float)((float)FIGHTER_ACTION_DELAY_MSECS) / 1000.0f)) {
		timer = float((float)clock() / (float)CLOCKS_PER_SEC);
		if (buttons.empty()) {
			sprite->SetAnimFilm(AFH.GetFilm("Idle"));
			animator->MarkAsRunning(animators->at("idle"));
			animator->MarkAsSuspended(animators->at("walk"));
			animator->MarkAsSuspended(animators->at("walkReverse"));
		}

		buttons.clear();

	}
}

void UpdateKeys() {
	SDL_Event _event;
	SDL_PollEvent(&_event);
	switch (_event.type)
	{

		case SDL_KEYDOWN: {
			if (_event.key.state == SDL_PRESSED)
			{
				buttons.push_back(_event.key.keysym.sym);
			}			
			break;
		}

	}
}

extern bool input::test_key(int32_t keyCode) {
	for (auto item : buttons) {
		if (item == keyCode) {
			return true;
		}
	}
	return false;
}