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
	void InitializeBattleUIAnimations(SDL_Renderer *renderer);
	virtual void InitializeUI();
	void RenderUI();
private:
	Fighter *player1, *player2;
	PlayerUI player1UI, player2UI;
	vector<SDL_Texture*> timerTextures;
	vector<SDL_Texture*> pointsTextures;
	float timer;
	int countdown = 99;

	AnimationFilmHolder*	afh;
	AnimatorHolder*		ah;
	typedef std::map<std::string, Animator*>	Animators;
	Animators *animators;
	SpritesHolder* sprites;
	bool flipped;
	int bmXs[4], bmYs[4];
};

