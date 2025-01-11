#pragma once
#include "Window.h"
#include <rendell_text.h>
#include "Viewport.h"

class App final
{
public:
	App();
	~App() = default;
	int run();

private:
	bool tryCreateMainWindow();
	bool initRendell();
	bool initTextRenderer();

	void setupViewport();
	void setupTextRenderer();

	int _result{ 0 };
	std::unique_ptr<Window> _mainWindow;
	ViewportSharedPtr _viewport;
	std::unique_ptr<rendell_text::TextRenderer> _textRenderer;
};