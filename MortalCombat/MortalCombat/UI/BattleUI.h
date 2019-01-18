#pragma once
#include "UICanvas.h"
#include <SDL.h>        
#include <SDL_image.h>
#include "../Fighter/Fighter.h"

class BattleUI : public UICanvas
{
public:
	BattleUI(SDL_Renderer* _renderer, Fighter* player1, Fighter* player2);
	
	virtual void InitializeUI();
	void RenderUI();
private:
	Fighter *player1, *player2;

	RenderElement* player1Lifebar;
	RenderElement* player1Coins;

	RenderElement* player2Lifebar;
	RenderElement* player2Coins;

};

