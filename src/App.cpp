#include<iostream>
#include <GLFW/glfw3.h>
#include <rendell/rendell.h>
#include "App.h"
#include "MainRenderingContext.h"

App::App()
{
	setupViewport();

	if (!tryCreateMainWindow())
	{
		std::cout << "Failed to create main window" << std::endl;
		_result = -1;
		return;
	}
	if (!initRendell())
	{
		std::cout << "Failed to initialize graphical api" << std::endl;
		_result = -1;
		return;
	}
	_mainWindow->setViewport(Viewport::getCurrent());
	_mainWindow->setRenderingContext(std::make_shared<MainRenderingContext>());
}

int App::run()
{
	if (_result != 0)
	{
		return _result;
	}

	while (_mainWindow->isOpen())
	{
		_mainWindow->update();
		_mainWindow->processEvents();
	}

	rendell::release();

	return _result;
}

bool App::tryCreateMainWindow()
{
	_mainWindow = std::make_unique<RenderingWindow>(600, 400, "Waxedit");
	if (Window::isInitialized())
	{
		_mainWindow->makeContextCurrent();
		return true;
	}
	return false;
}

bool App::initRendell()
{
	rendell::Initer initer;
	initer.context = static_cast<void*>(glfwGetProcAddress);
	const bool result = rendell::init(initer);
	if (result)
	{
		rendell::setPixelUnpackAlignment(1);
	}
	return result;
}

void App::setupViewport()
{
	ViewportSharedPtr viewport = std::make_shared<Viewport>();
	Viewport::setCurrent(viewport);
}
