#include "OptionsUI.h"

OptionsUI::OptionsUI()
{
	
}

void OptionsUI::InitializeUI()
{
	InitializeImageElement("./Bitmaps/Options/OptionsTheme.png", { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT });
}

void OptionsUI::RenderUI()
{
	UICanvas::RenderUI();
}

