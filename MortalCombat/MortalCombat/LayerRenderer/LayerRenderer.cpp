#include "LayerRenderer.h"

void LayerRenderer::InitializeImageElement(string imagefile, Layer renderLayer, SDL_Rect imageRect)
{
	RenderElement element;
	const char *imFile = imagefile.c_str();

	//Preload texture
	element.texture = IMG_LoadTexture(renderer, imFile);
	element.renderLayer = renderLayer;
	element.imageRect = imageRect;

	if (renderLayer == Layer::Foreground) {
		foregroundList.push_back(element);
	}
	else if (renderLayer == Layer::Action) {
		actionList.push_back(element);
	}
	else if (renderLayer == Layer::Background) {
		backgroundList.push_back(element);
	}
}

void LayerRenderer::RenderLayer(Layer renderLayer)
{
	vector<RenderElement>* tempVector = NULL;

	if (renderLayer == Layer::Foreground) {
		tempVector = &foregroundList;
	}
	else if (renderLayer == Layer::Action) {
		tempVector = &actionList;
	}
	else if (renderLayer == Layer::Background) {
		tempVector = &backgroundList;
	}

	for (RenderElement element : *tempVector)
	{
		SDL_RenderCopy(renderer, element.texture, NULL, &element.imageRect);
	}
}

void LayerRenderer::ClearLayerRenderer()
{
	backgroundList.clear();
	actionList.clear();
	foregroundList.clear();
	//SDL_DestroyTexture
}


LayerRenderer::LayerRenderer(SDL_Renderer* _renderer)
{
	renderer = _renderer;
}

