#pragma once
#include <SDL.h>        
#include <SDL_image.h>
#include <string>
#include <vector>
#include "../Animator/Sprites/AnimationFilms/AnimationFilmHolder.h"
#include "../Animator/Animator/AnimatorHolder.h"
#include "../Animator/Sprites/Sprite/SpritesHolder.h"
using namespace std;

class UICanvas
{
public:
	int tag;
	int GetSceneTag();

	virtual void InitializeUI() = 0;
	virtual void RenderUI();
	virtual void InvokeMethod(string key);
	virtual void FireAnimation(string animationNamde, int destroytime);
	virtual void KillAnimation(string animationNamde);

	struct RenderElement {
		SDL_Rect imageRect;
		SDL_Rect imageSourceRect;
		SDL_Texture* texture;
	};
	
protected:
	SDL_Renderer* renderer;
	vector<RenderElement*> elementList;

	RenderElement* InitializeImageElement(string imagefile, SDL_Rect imageRect);
	
	typedef map<string, Animator*>	Animators;
	Animators *animators;
};

