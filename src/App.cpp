#include<iostream>
#include <GLFW/glfw3.h>
#include <rendell/rendell.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "App.h"
#include "Window.h"
#include "Shaders/ShaderStorage.h"
#include "Widgets/Rectangle.h"
#include "Widgets/Text.h"
#include <vector>

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
	setupViewport();
	if (!initRendell())
	{
		std::cout << "Failed to initialize graphical api" << std::endl;
		_result = -1;
		return;
	}
}

int App::run()
{
	if (_result != 0)
	{
		return _result;
	}

	rendell::setClearBits(rendell::colorBufferBit | rendell::depthBufferBit);

	ShaderStorage::init();

	Rectangle* rectangle = new Rectangle();
	rectangle->getTransform().setPosition(glm::vec2(100.0f, 100.0f));
	rectangle->getTransform().setScale(glm::vec2(50.0f, 50.0f));
	rectangle->setColor(glm::vec4(1.0f, 0.7f, 0.5f, 1.0f));

	Text* text = new Text();
	text->setText(L"Hello World!");
	text->setFontPath("../res/Fonts/mononoki/mononoki-Regular.ttf");
	text->setFontSize(glm::vec2(FONT_WIDTH, FONT_HEIGHT));
	text->setBackgroundColor(glm::vec4(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1.0f));
	text->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	text->getTransform().setPosition(glm::vec2(50.0f, 50.0f));

	_widgets.push_back(WidgetSharedPtr(rectangle));
	_widgets.push_back(WidgetSharedPtr(text));

	while (_mainWindow->isOpen())
	{
		rendell::clear();
		rendell::clearColor(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1);

		for (const WidgetSharedPtr& widget : _widgets)
		{
			widget->draw();
		}

		_mainWindow->swapBuffers();
		_mainWindow->processEvents();
	}

	ShaderStorage::release();

	rendell::release();

	return _result;
}

bool App::tryCreateMainWindow()
{
	_mainWindow.reset(new Window(600, 400, "Waxedit"));
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
	const glm::mat4 projectMat = glm::ortho(0.0f, 600.0f, 0.0f, 400.0f, 0.1f, 100.0f);
	const glm::mat4 viewMat = glm::mat4(1.0f);

	_viewport = std::make_shared<Viewport>();
	_viewport->setProjectMat(projectMat);
	_viewport->setViewMat(viewMat);
	Viewport::setCurrent(_viewport);
}
