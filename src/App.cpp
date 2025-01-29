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

	rendell_ui::Rectangle* rectangle = new rendell_ui::Rectangle(rootWidget.get());
	rectangle->setColor(glm::vec4(1.0f, 0.7f, 0.5f, 1.0f));
	rectangle->setMargins(30, 100, 20, 0);
	rectangle->setAnchor(rendell_ui::Anchor::topStretch);

	rendell_ui::Rectangle* redRectangle = new rendell_ui::Rectangle(rectangle);
	redRectangle->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	redRectangle->setSize(glm::vec2(50.0f, 50.0f));
	redRectangle->setAnchor(rendell_ui::Anchor::rightBottom);
	redRectangle->setMargins(0, 10, 20, 0);

	rendell_ui::Text* text = new rendell_ui::Text(rootWidget.get());
	text->setText(L"Hello World!");
	text->setFontPath("../res/Fonts/mononoki/mononoki-Regular.ttf");
	text->setFontSize(glm::vec2(FONT_WIDTH, FONT_HEIGHT));
	text->setBackgroundColor(glm::vec4(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1.0f));
	text->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	text->setOffset(glm::vec2(-100.0f, -100.0f));
	text->setAnchor(rendell_ui::Anchor::center);

	_canvas->addWidget(rootWidget);

	auto renderer = _renderer;
	auto window = _mainWindow;

	_canvas->setRefreshedCallback([renderer, window](int width, int height) {
		renderer->startFrame();
		renderer->render();
		window->swapBuffers();
		renderer->endFrame();
		renderer->cooldown();
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
	initer.context = static_cast<void*>(glfwGetProcAddress);
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
