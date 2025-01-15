#pragma once
#include "Window.h"

class MainWindow final : public Window
{
public:
	MainWindow(int width, int height, const char* title);
	~MainWindow() = default;

private:
	void onRefreshed() override;
};