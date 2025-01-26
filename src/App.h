#pragma once
#include "RenderingWindow.h"

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
	std::unique_ptr<RenderingWindow> _mainWindow;
};