#pragma once
class KeyboardController
{
public:
	KeyboardController();
	void Update();

private:
	bool optionsOpen;
	bool optionsUP, optionsDown;
};

