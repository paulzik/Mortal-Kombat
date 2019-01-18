#pragma once
#include "UICanvas.h"
#include <SDL.h>        
#include <SDL_image.h>
#include "../Fighter/Fighter.h"

class BattleUI : public UICanvas
{
public:
	struct PlayerUI
	{
		RenderElement* lifebarRed;
		RenderElement* lifebarGreen;
		RenderElement* name;
		vector<RenderElement*> coins;
	};

	

	BattleUI(Fighter* player1, Fighter* player2);
	
	virtual void InitializeUI();
	void RenderUI();
private:
	Fighter *player1, *player2;
	PlayerUI player1UI, player2UI;

};

