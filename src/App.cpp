#include<iostream>
#include <rendell/rendell.h>
#include <rendell_ui/rendell_ui.h>
#include <chrono>
#include <thread>
#include "App.h"
#include "Renderer.h"

#define FONT_WIDTH 32.0f
#define FONT_HEIGHT 32.0f
#define BACKGROUND_COLOR 31.0f / 255.0

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
	_canvas = std::make_shared<Canvas>(_viewport);
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

	rendell_ui::WidgetSharedPtr rootWidget = std::make_shared<rendell_ui::Widget>();
	rootWidget->setAnchor(rendell_ui::Anchor::centerStretch);

	rendell_ui::TextEdit* textEdit = new rendell_ui::TextEdit(rootWidget.get());
	textEdit->setSize(glm::vec2(50, 50));
	textEdit->setMargins(0, 0, 0, 0);
	textEdit->setAnchor(rendell_ui::Anchor::centerStretch);
	textEdit->setText(LR"(#include <iostream>

int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}
	)");


	_canvas->addWidget(rootWidget);

	auto renderer = _renderer;
	auto window = _mainWindow;

	_canvas->setRefreshedCallback([renderer, window](int width, int height) {
		renderer->startFrame();
		renderer->render();
		window->swapBuffers();
		renderer->endFrame();
		});

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
	return true;
}

bool App::initRendell()
{
	rendell::Initer initer;
	initer.context = reinterpret_cast<void*>(glfwGetProcAddress);
	const bool result = rendell::init(initer);
	if (result)
	{
		rendell::setPixelUnpackAlignment(1);
		rendell::setClearBits(rendell::colorBufferBit | rendell::depthBufferBit);
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
