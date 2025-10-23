#include<iostream>
#include <rendell/rendell.h>
#include <rendell_ui/rendell_ui.h>
#include <chrono>
#include <thread>
#include "App.h"
#include "Renderer.h"
#include "Editor/Editor.h"

App::App()
{
	if (!rendell_ui::init())
	{
		std::cout << "Failed to initialize Rendell-UI" << std::endl;
		exit(-1);
	}
	_mainWindow = rendell_ui::createWindow(600, 400, "Waxedit");

	setupViewport();
	_renderer = makeRenderer(_viewport);
	_canvas = makeEditorCanvas(_viewport);
	_mainWindow->setEventHandler(_canvas);

	_invoker = makeInvoker();

	_hotkeyHandler = makeHotkeyHandler();
	_hotkeyHandler->setInvoker(_invoker);

	Editor::init(_canvas);
}

App::~App()
{
	Editor::release();
	_renderer.reset();
	_hotkeyHandler.reset();
	_viewport.reset();
	_canvas.reset();
	_invoker.reset();
	rendell_ui::release();
}

int App::run()
{
	if (_result != 0)
	{
		return _result;
	}

	_canvas->setHotkeyHandler(_hotkeyHandler);

	auto renderer = _renderer;
	auto window = _mainWindow;

	_canvas->setRefreshedCallback([renderer, window](int width, int height) {
		renderer->startFrame();
		renderer->render();
		renderer->endFrame();
		});

	while (_mainWindow->isOpen())
	{
		_renderer->startFrame();
		_renderer->render();
		_mainWindow->processEvents();
		_renderer->endFrame();
		_mainWindow->waitEvent();
	}

	return _result;
}

void App::setupViewport()
{
	_viewport = rendell_ui::makeViewport();
	rendell_ui::Viewport::setCurrent(_viewport);
}
