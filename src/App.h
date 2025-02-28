#pragma once
#include <rendell_ui/rendell_ui.h>
#include "Canvas.h"
#include "HotkeyHandler.h"
#include "IRenderer.h"
#include "Editor/Commands/Invoker.h"

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
	HotkeyHandlerSharedPtr _hotkeyHandler;

	rendell_ui::WindowSharedPtr _mainWindow;
	rendell_ui::ViewportSharedPtr _viewport;
	CanvasSharedPtr _canvas;
	InvokerSharedPtr _invoker;
};