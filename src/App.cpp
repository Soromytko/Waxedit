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
	_renderer = std::make_shared<Renderer>(_viewport);
	_canvas = std::make_shared<rendell_ui::Canvas>(_viewport);
	_mainWindow->setEventHandler(_canvas);

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

	auto rectangle = std::make_shared< rendell_ui::Rectangle>(nullptr);
	rectangle->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	rectangle->setAnchor(rendell_ui::Anchor::leftTop);

	_canvas->addWidget(rectangle);

	while (_mainWindow->isOpen())
	{
		_renderer->startFrame();
		_renderer->render();
		_mainWindow->swapBuffers();
		_mainWindow->processEvents();
		_renderer->endFrame();
		_renderer->cooldown();
	}

	return _result;
}

bool App::tryCreateMainWindow()
{
	_mainWindow = std::make_unique<rendell_ui::Window>(600, 400, "Waxedit");
	if (!_mainWindow->isInitialized())
	{
		return false;
	}
	_mainWindow->makeContextCurrent();
	_mainWindow->setEventHandler(std::make_shared<rendell_ui::Canvas>(_viewport));
	return true;
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
	_viewport = std::make_shared<rendell_ui::Viewport>();
	rendell_ui::Viewport::setCurrent(_viewport);
}
