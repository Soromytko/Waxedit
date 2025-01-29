#pragma once
#include <rendell_ui/rendell_ui.h>
#include "IRenderer.h"

class App final
{
public:
	App();
	~App();
	int run();

private:
	bool tryCreateMainWindow();
	bool initRendell();
	bool initRendellUI();

	void setupViewport();

	int _result{ 0 };
	
	IRendererSharedPtr _renderer;
	rendell_ui::WindowSharedPtr _mainWindow;
	rendell_ui::ViewportSharedPtr _viewport;
	rendell_ui::CanvasSharedPtr _canvas;
};