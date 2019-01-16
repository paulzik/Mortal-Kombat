#pragma once
#include <string>
#include <SDL.h>        
#include <vector>
#include <SDL_image.h>

using namespace std;

class LayerRenderer {

public:
	enum Layer
	{
		Background,
		Action,
		Foreground,
	};

private:
	SDL_Renderer* renderer;

	struct RenderElement {
		Layer renderLayer;
		SDL_Rect imageRect;
		SDL_Texture* texture;
	};

	vector<RenderElement> backgroundList;
	vector<RenderElement> actionList;
	vector<RenderElement> foregroundList;

public:
	void InitializeImageElement(string imagefile, Layer renderLayer, SDL_Rect imageRect);
	void RenderLayer(Layer renderLayer);
	void ClearLayerRenderer();
	LayerRenderer(SDL_Renderer* _renderer);
};