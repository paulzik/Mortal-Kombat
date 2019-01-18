#pragma once
#include "UICanvas.h"
#include <SDL.h>        
#include <SDL_image.h>

class BattleUI : public UICanvas
{
public:
	BattleUI(SDL_Renderer* _renderer);
	
	virtual void InitializeUI();

private:
	RenderElement* player1Lifebar;
	RenderElement* player1Coins;

	RenderElement* player2Lifebar;
	RenderElement* player2Coins;



};

