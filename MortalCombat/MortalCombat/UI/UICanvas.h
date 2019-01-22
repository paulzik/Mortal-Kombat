#pragma once
#include <SDL.h>        
#include <SDL_image.h>
#include <string>
#include <vector>
//#include "UIManager.h"
using namespace std;

class UICanvas
{
public:
	//SceneTag tag;
	
	//SceneTag GetSceneTag();
	virtual void InitializeUI() = 0;
	virtual void RenderUI();
	virtual void InvokeMethod(string key);
	struct RenderElement {
		SDL_Rect imageRect;
		SDL_Rect imageSourceRect;
		SDL_Texture* texture;
	};
	
protected:
	SDL_Renderer* renderer;
	vector<RenderElement*> elementList;

	RenderElement* InitializeImageElement(string imagefile, SDL_Rect imageRect);
	
};

