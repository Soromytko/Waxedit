#pragma once
#include "Window.h"
#include "Widgets/Widget.h"
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

	void setupViewport();

	int _result{ 0 };
	std::unique_ptr<Window> _mainWindow;
	ViewportSharedPtr _viewport;

	std::vector<WidgetSharedPtr> _widgets;
};