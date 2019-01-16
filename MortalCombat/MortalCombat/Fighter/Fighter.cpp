#include "Fighter.h"

Fighter::Fighter(FighterTag _tag)
{
	tag = _tag;
	health = 100.0;
	isAlive = true;
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
