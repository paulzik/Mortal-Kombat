#include "Fighter.h"
#include "../UI/UIManager.h";

Fighter::Fighter(FighterTag _tag, int _playerID)
{
	tag = _tag;
	health = 100.0;
	isAlive = true;
	playerID = _playerID;
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
	//UIManager::Get().G
}

float Fighter::GetHealth()
{
	return health;
}
