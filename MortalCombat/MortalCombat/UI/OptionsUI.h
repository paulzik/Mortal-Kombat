#pragma once
#include "UICanvas.h"
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 508

class OptionsUI : public UICanvas
{
public:

	OptionsUI();
	virtual void InitializeUI();
	void RenderUI();
};

