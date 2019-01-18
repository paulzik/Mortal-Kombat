#pragma once
#include <SDL.h>        
#include <SDL_image.h>
#include <string>
#include <vector>

using namespace std;

class UICanvas
{
public:
	UICanvas();

	virtual void InitializeUI() = 0;
	virtual void RenderUI();

	struct RenderElement {
		SDL_Rect imageRect;
		SDL_Texture* texture;
	};

protected:
	SDL_Renderer* renderer;
	vector<RenderElement*> elementList;

	RenderElement* InitializeImageElement(string imagefile, SDL_Rect imageRect);

};

