#include "UICanvas.h"
#include "../Animator/Animator/AnimatorHolder.h"


int UICanvas::GetSceneTag()
{
	return tag;
}

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

void UICanvas::FireAnimation(string animationNamde, int destroytime)
{
	AnimatorHolder::MarkAsRunning(animators->at(animationNamde));
}

void UICanvas::KillAnimation(string animationNamde)
{
	AnimatorHolder::MarkAsSuspended(animators->at(animationNamde));
	AnimatorHolder::Cancel(animators->at(animationNamde));
}

void UICanvas::RenderUI()
{
	for (RenderElement* element : elementList)
	{
		SDL_RenderCopy(renderer, element->texture, NULL, &element->imageRect);
	}
}

