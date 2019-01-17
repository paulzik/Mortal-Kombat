#include "Fighter.h"
Direction direction = Direction::none;

Fighter::Fighter(FighterTag _tag, SDL_Renderer *renderer)
{
	tag = _tag;
	health = 100.0;
	isAlive = true;

	InitializeCharacter(_tag, renderer);

	sprite->SetAnimFilm(AFH->GetFilm("Idle"));
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
	inputController.Handle();
	for (auto item : inputController.GetLogical()) {
		if (item == "moveforward") {
			sprite->SetAnimFilm(AFH->GetFilm("Walk"));
			animator->MarkAsRunning(animators->at("walk"));
			animator->MarkAsSuspended(animators->at("walkReverse"));
		}
		//else if (direction == Direction::none) {
		//	sprite->SetAnimFilm(AFH->GetFilm("Idle"));
		//	animator->MarkAsRunning(animators->at("idle"));
		//	animator->MarkAsSuspended(animators->at("walk"));
		//	animator->MarkAsSuspended(animators->at("walkReverse"));
		//}
		else if (item == "movebackward") {
			sprite->SetAnimFilm(AFH->GetFilm("Walk"), true);
			animator->MarkAsRunning(animators->at("walkReverse"));
			animator->MarkAsSuspended(animators->at("walk"));
		}
	}


	animator->Progress(float((float)clock() / (float)CLOCKS_PER_SEC));
	animator->Render(Renderer);

}

extern bool input::test_key(int32_t keyCode) {
	SDL_Event _event;
	SDL_PollEvent(&_event);
	switch (_event.type)
	{

		case SDL_KEYDOWN: {
			if (keyCode == _event.key.keysym.sym) {
				
				return true;
			}
			
			break;
		}
		case SDL_KEYUP: {
			if (keyCode == _event.key.keysym.sym) {
				
				return false;
			}
			
			break;
		}
	}
	return false;


}