#include "RenderingWindow.h"
#include <glm/gtc/matrix_transform.hpp>
#include <rendell/rendell.h>
#include <rendell_ui/rendell_ui.h>

RenderingWindow::RenderingWindow(int width, int height, const char* title) :
	Window(width, height, title)
{

}

void RenderingWindow::startFrame()
{
	_frameStartTimePoint = Clock::now();
}

void RenderingWindow::update()
{
	_viewport->apply();
	_renderingContext->render();

	swapBuffers();
}

void RenderingWindow::endFrame()
{
	_frameEndTimePoint = Clock::now();
	_deltaTime = std::chrono::duration<double>(_frameEndTimePoint - _frameStartTimePoint).count();

	const double sleepTime = _targetFrameTime - _deltaTime;
	if (sleepTime > 0)
	{
		cooldown(sleepTime);
	}

	_fps = static_cast<int>(1.0 / (_deltaTime + sleepTime));
}

void RenderingWindow::setTargetFPS(uint32_t value)
{
	_targetFps = value;
	_targetFrameTime = 1.0 / _targetFps;
}

void RenderingWindow::setViewport(rendell_ui::ViewportSharedPtr viewport)
{
	_viewport = viewport;
}

void RenderingWindow::setRenderingContext(RenderingContextSharedPtr renderingContext)
{
	_renderingContext = renderingContext;
}

uint32_t RenderingWindow::getFPS() const
{
	return _fps;
}

uint32_t RenderingWindow::getTargetFPS() const
{
	return _targetFps;
}

double RenderingWindow::getDeltaTime() const
{
	return _deltaTime;
}

const rendell_ui::ViewportSharedPtr RenderingWindow::getViewport() const
{
	return _viewport;
}

const RenderingContextSharedPtr RenderingWindow::getRenderingContext() const
{
	return _renderingContext;
}

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void sleep_microseconds(long long microseconds) {
#ifdef _WIN32
	LARGE_INTEGER frequency;
	LARGE_INTEGER start, end;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	long long ticksToWait = (microseconds * frequency.QuadPart) / 1000000;

	if (ticksToWait <= 0)
	{
		return;
	}
	do
	{
		QueryPerformanceCounter(&end);
	} while (end.QuadPart - start.QuadPart < ticksToWait);

#else
	usleep(microseconds);
#endif
	}

void RenderingWindow::cooldown(double sleepTime)
{
	assert(sleepTime > 0);
	sleep_microseconds(static_cast<long long>(sleepTime * 1000000.0));
}

void RenderingWindow::onRefreshed()
{
	const glm::ivec2 size = getSize();
	const int width = size.x, height = size.y;

	const float ratio = (float)width / (float)height;
	const float worldWidth = height * ratio;

	const float halfWidth = worldWidth * 0.5f;
	const float halfHeight = height * 0.5f;

	const glm::mat4 projectMat = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0f, 1.0f);
	_viewport->setProjectMat(projectMat);
	_viewport->setParameters(0, 0, width, height);

	_renderingContext->onViewportUpdated(0, 0, width, height);

	startFrame();
	update();
	endFrame();

	// Make sure the rendering result is actually visible.
	rendell::finish();
}
