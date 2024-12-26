#pragma once
#include "Window.h"
#include <rendell_text.h>

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
	void setupTextRenderer();

	int _result{ 0 };
	std::unique_ptr<Window> _mainWindow;
	std::unique_ptr<rendell_text::TextRenderer> _textRenderer;
};