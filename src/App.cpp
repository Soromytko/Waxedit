#include<iostream>
#include <rendell/rendell.h>
#include <rendell_ui/rendell_ui.h>
#include <chrono>
#include <thread>
#include "App.h"
#include "Renderer.h"

App::App()
{
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
	if (!initRendellUI())
	{
		std::cout << "Failed to initialize Rendell-UI" << std::endl;
		_result = -1;
		return;
	}
	setupViewport();
	_mainWindow->setViewport(rendell_ui::Viewport::getCurrent());
	_mainWindow->setRenderingContext(std::make_shared<Renderer>());

}

App::~App()
{
	rendell::release();
	rendell_ui::release();
}

int App::run()
{
	if (_result != 0)
	{
		return _result;
	}

	while (_mainWindow->isOpen())
	{
		_mainWindow->startFrame();
		_mainWindow->update();
		_mainWindow->processEvents();
		_mainWindow->endFrame();
	}

	return _result;
}

bool App::tryCreateMainWindow()
{
	_mainWindow = std::make_unique<RenderingWindow>(600, 400, "Waxedit");
	if (rendell_ui::Window::isInitialized())
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

bool App::initRendellUI()
{
	return 	rendell_ui::init();
}

void App::setupViewport()
{
	rendell_ui::ViewportSharedPtr viewport = std::make_shared<rendell_ui::Viewport>();
	rendell_ui::Viewport::setCurrent(viewport);
}
