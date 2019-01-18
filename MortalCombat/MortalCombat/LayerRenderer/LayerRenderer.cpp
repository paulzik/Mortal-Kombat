#include "LayerRenderer.h"
#include "../UI/UIManager.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 508

void LayerRenderer::DisplayBattleUI()
{
	InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", LayerRenderer::Layer::Foreground, { 42,58,163 * 2,12 * 2 });
	InitializeImageElement("./Bitmaps/BattleElements/lifebar.png", LayerRenderer::Layer::Foreground, { 412,58,163 * 2,12 * 2 });

	InitializeImageElement("./Bitmaps/BattleElements/lifebarGreen.png", LayerRenderer::Layer::Foreground, { 44,60,120 * 2,10 * 2 });
	InitializeImageElement("./Bitmaps/BattleElements/lifebarGreen.png", LayerRenderer::Layer::Foreground, { 414,60,120 * 2,10 * 2 });

	InitializeImageElement("./Bitmaps/BattleElements/coin.png", LayerRenderer::Layer::Foreground, { 50,90,10 * 2,10 * 2 });
	InitializeImageElement("./Bitmaps/BattleElements/coin.png", LayerRenderer::Layer::Foreground, { 80,90,10 * 2,10 * 2 });
}

void LayerRenderer::DisplayStartScreenUI()
{
	InitializeImageElement("./Bitmaps/Menu/StartScreen.png", LayerRenderer::Layer::Background, { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT });
}

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

	//DisplayBattleUI();
	UIManager::Get()->InitializeCurrentScene(_renderer);
}

