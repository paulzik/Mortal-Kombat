#include "UICanvas.h"



void UICanvas::InitializeUI() {
}

void UICanvas::InvokeMethod(string key) {
}

UICanvas::RenderElement* UICanvas::InitializeImageElement(string imagefile, SDL_Rect imageRect)
{
	RenderElement* element = new RenderElement;
	const char *imFile = imagefile.c_str();
	
	//Preload texture
	element->texture = IMG_LoadTexture(renderer, imFile);
	element->imageRect = imageRect;
	elementList.push_back(element);
	
	return elementList[elementList.size()-1];
}

void UICanvas::RenderUI()
{
	for (RenderElement* element : elementList)
	{
		SDL_RenderCopy(renderer, element->texture, NULL, &element->imageRect);
	}
}

