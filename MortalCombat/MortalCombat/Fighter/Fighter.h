#pragma once

enum FighterTag {SubZero, Scorpion};

class Fighter final {
private:

	//TODO
	//engine2d::Sprite*			sprite = nullptr;
	//std::string					nextAction;
	//engine2d::TickAnimator*		tickAnimator = nullptr;	// deferred firing actions; always dynamic
	//engine2d::TickAnimation		tickAnim;
	//input::InputController		inputController;
	//logic::StateTransitions		stateTransitions;

	float health;
	FighterTag tag;
	bool isAlive;
	int numberOfWins;

public:
	Fighter(FighterTag _tag);
	bool PlayerIsAlive();
	void DamagePlayer(int damage);
	float GetHealth();
};