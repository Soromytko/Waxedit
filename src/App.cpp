#include<iostream>
#include <GLFW/glfw3.h>
#include <rendell/rendell.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "App.h"
#include "Window.h"
#include <vector>

#define FONT_WIDTH 32.0f
#define FONT_HEIGHT 32.0f
#define BACKGROUND_COLOR 31.0f / 255.0

struct Matrices
{
	glm::mat4 projectMat = glm::mat4(1.0);
	glm::mat4 viewMat = glm::mat4(1.0);
	glm::mat4 worldMat = glm::mat4(1.0);
};

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
	if (!initTextRenderer())
	{
		std::cout << "Failed to initialize TextRenderer" << std::endl;
		_result = -1;
		return;
	}
	setupTextRenderer();
}

int App::run()
{
	if (_result != 0)
	{
		return _result;
	}

	rendell::setClearBits(rendell::colorBufferBit | rendell::depthBufferBit);

	_textRenderer->setText(L"Hello World!");

	while (_mainWindow->isOpen())
	{
		rendell::clear();
		rendell::clearColor(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1);

		_textRenderer->draw();

		_mainWindow->swapBuffers();
		_mainWindow->processEvents();
	}

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

bool App::initTextRenderer()
{
	_textRenderer.reset(new rendell_text::TextRenderer);
	return _textRenderer->isInitialized();
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

void App::setupTextRenderer()
{
	//Matrices
	Matrices matrices;
	matrices.projectMat = glm::ortho(0.0f, 600.0f, 0.0f, 400.0f, 0.1f, 100.0f);
	matrices.worldMat = glm::translate(glm::mat4(1.0), glm::vec3(10.0, 10.0, 0.0));
	glm::mat4 matrix = matrices.projectMat * matrices.viewMat * matrices.worldMat;
	_textRenderer->setMatrix(matrix);

	//Font
	_textRenderer->setFontPath("../res/Fonts/mononoki/mononoki-Regular.ttf");
	_textRenderer->setFontSize(glm::vec2(FONT_WIDTH, FONT_HEIGHT));

	//Color
	_textRenderer->setColor(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
	_textRenderer->setBackgroundColor(glm::vec4(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1.0f));
}
