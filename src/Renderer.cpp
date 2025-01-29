#include "Renderer.h"
#include <rendell_ui/rendell_ui.h>

#define FONT_WIDTH 32.0f
#define FONT_HEIGHT 32.0f
#define BACKGROUND_COLOR 31.0f / 255.0

Renderer::Renderer(rendell_ui::ViewportSharedPtr viewport) :
	_viewport(viewport)
{

}

Renderer::~Renderer()
{

}

void Renderer::startFrame()
{
	_frameStartTimePoint = Clock::now();
}

void Renderer::endFrame()
{
	_frameEndTimePoint = Clock::now();
	_deltaTime = std::chrono::duration<double>(_frameEndTimePoint - _frameStartTimePoint).count();
	_sleepTime = _targetFrameTime - _deltaTime;
	_fps = static_cast<int>(1.0 / (_deltaTime + _sleepTime));
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

void Renderer::cooldown()
{
	if (_sleepTime > 0)
	{
		sleep_microseconds(static_cast<long long>(_sleepTime * 1000000.0));
	}
}

void Renderer::render() const
{
	_viewport->apply();

	rendell::clear();
	rendell::clearColor(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1);

	rendell_ui::draw();
}
