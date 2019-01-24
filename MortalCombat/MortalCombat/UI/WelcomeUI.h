#pragma once
#include "UICanvas.h"
class WelcomeUI :
	public UICanvas
{
public:
	WelcomeUI();
	virtual void InitializeUI();
	void RenderUI();
private:
	RenderElement* background;
};

