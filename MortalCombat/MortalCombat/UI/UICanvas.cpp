#include "UICanvas.h"



UICanvas::UICanvas()
{
}


void UICanvas::InitializeUI() {
}

UICanvas::RenderElement* UICanvas::InitializeImageElement(string imagefile, SDL_Rect imageRect)
{
	RenderElement element;
	const char *imFile = imagefile.c_str();
	
	//Preload texture
	element.texture = IMG_LoadTexture(renderer, imFile);
	element.imageRect = imageRect;
	
	elementList.push_back(element);
	
	return &element;
}

void UICanvas::RenderUI()
{
	for (RenderElement element : elementList)
	{
		SDL_RenderCopy(renderer, element.texture, NULL, &element.imageRect);
	}
}

