#pragma once
#include "../Fighter/Fighter.h"
#include "../UI/UIManager.h";

class KeyboardController
{
public:
	KeyboardController();
	void Update(Fighter* p1, Fighter* p2);

	void AddKey(Fighter* _fighter, std::string _key);
	void RemoveKey(Fighter* _fighter, std::string _key);

private:
	bool optionsOpen;
	bool optionsUP, optionsDown;
};

