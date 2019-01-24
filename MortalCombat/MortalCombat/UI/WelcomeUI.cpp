#include "WelcomeUI.h"
#include "../UI/UIManager.h"

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 508

WelcomeUI::WelcomeUI()
{
	renderer = UIManager::Get()->GetRenderer();

	tag = SceneTag::Welcome;
	InitializeUI();
}

void WelcomeUI::InitializeUI()
{
	background = InitializeImageElement("./Bitmaps/Menu/StartScreen.png", { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
}

void WelcomeUI::RenderUI()
{
	UICanvas::RenderUI();
}
