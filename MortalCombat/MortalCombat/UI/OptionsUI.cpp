#include "OptionsUI.h"
#include "UIManager.h"

OptionsUI::OptionsUI()
{
	renderer = UIManager::Get()->GetRenderer();
	selectedOption = 0;

	InitializeUI();
}

void OptionsUI::InitializeUI()
{
	//Initialize Background
	InitializeImageElement("./Bitmaps/Options/OptionsBackGround.png", { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT });

	//Intialize Option Boxes Textures
	selectedBox = IMG_LoadTexture(renderer, "./Bitmaps/Options/BoxGreen.png");
	unselectedBox = IMG_LoadTexture(renderer, "./Bitmaps/Options/BoxWhite.png");

	//Initialize selection Triange
	selectionTriangle = IMG_LoadTexture(renderer, "./Bitmaps/Options/Triangle.png");

	//Initialize Option elements
	AddOption("./Bitmaps/Options/SpeedOption.png", 3);
	AddOption("./Bitmaps/Options/SoundOption.png", 3);
	AddOption("./Bitmaps/Options/TinyModeOption.png", 1);
	AddOption("./Bitmaps/Options/GodModeOption.png", 1);

	//Initialize Configurations
	optionsVector[0].selectedBox = 1;
	optionsVector[1].selectedBox = 0;
	optionsVector[2].selectedBox = -1;
	optionsVector[3].selectedBox = -1;




}



void OptionsUI::RenderUI()
{
	UICanvas::RenderUI();

	//Render selection triangle
	SDL_Rect rect = SDL_Rect({ 230 ,(selectedOption * 50) + 180, 27, 27 });	
	SDL_RenderCopy(renderer, selectionTriangle, NULL, &rect);

	//Render boxes
	for (size_t i = 0; i < optionsVector.size(); i++)
	{
		for (size_t j = 0; j < optionsVector[i].boxRect.size(); j++)
		{
			if (optionsVector[i].selectedBox + 1 > j) {
				SDL_RenderCopy(renderer, selectedBox, NULL, &optionsVector[i].boxRect[j]);
			}
			else {
				SDL_RenderCopy(renderer, unselectedBox, NULL, &optionsVector[i].boxRect[j]);
			}
		}
	}
}

void OptionsUI::AddOption(string optionImage, int numberOfBoxes)
{
	InitializeImageElement(optionImage, { 260, lastOptionY, 249, 45 });

	optionBoxes customBoxes;
	for (size_t i = 0; i < numberOfBoxes; i++)
	{
		RenderElement* element = new RenderElement;
		SDL_Rect imageRect = { 480 + (i*45), lastOptionY + 10, 27, 27 };

		element->imageRect = imageRect;
		//elementList.push_back(element);
		
		customBoxes.boxRect.push_back(element->imageRect);
	}
	optionsVector.push_back(customBoxes);
	lastOptionY += 50;
}

void OptionsUI::TraverseBoxes(int nextPrevID)
{
	//selectedBox -1 equals to no selection
	if (nextPrevID == 1) {
		if (optionsVector[selectedOption].selectedBox == optionsVector[selectedOption].boxRect.size() - 1)
			return;
		optionsVector[selectedOption].selectedBox++;
	}
	else if (nextPrevID == -1) {
		if (optionsVector[selectedOption].selectedBox == -1)
			return;
		optionsVector[selectedOption].selectedBox--;
	}
}

void OptionsUI::TraverseOptions(int nextPrevID)
{
	if (nextPrevID == 1) {
		if (optionsVector.size() == selectedOption + 1)
			return;
		selectedOption++;
	}
	else if (nextPrevID == -1) {
		if (selectedOption == 0)
			return;
		selectedOption--;
	}
}

void OptionsUI::InvokeMethod(string key) 
{
	if (key == "w") {
		TraverseOptions(-1);
	}else if (key == "s") {
		TraverseOptions(1);
	}
	else if (key == "a") {
		TraverseBoxes(-1);
	}
	else if (key == "d") {
		TraverseBoxes(1);
	}
}
