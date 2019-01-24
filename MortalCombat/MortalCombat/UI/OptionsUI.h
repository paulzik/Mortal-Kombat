#pragma once
#include "UICanvas.h"
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 508

class OptionsUI : public UICanvas
{
public:

	OptionsUI();
	virtual void InitializeUI();
	void RenderUI();
	virtual void InvokeMethod(string key);
private:
	struct optionBoxes
	{
		vector<SDL_Rect> boxRect;
		int selectedBox;
	};
	vector<optionBoxes> optionsVector;
	
	SDL_Texture* selectedBox;
	SDL_Texture* unselectedBox;
	SDL_Texture* selectionTriangle;
	int selectedOption;
	int lastOptionY = 173;
	void AddOption(string optionImage, int numberOfBoxes);
	void TraverseBoxes(int nextPrevID);
	void TraverseOptions(int nextPrevID);
	void UpdateConfiguration();
};

