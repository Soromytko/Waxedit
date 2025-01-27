#pragma once
#include <rendell_ui/rendell_ui.h>
#include "IRenderingContext.h"
#include <memory>
#include <chrono>

class RenderingWindow final : public rendell_ui::Window
{
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

public:
	RenderingWindow(int width, int height, const char* title);
	~RenderingWindow() = default;

	void startFrame();
	void update();
	void endFrame();

	void setTargetFPS(uint32_t value);
	void setViewport(rendell_ui::ViewportSharedPtr viewport);
	void setRenderingContext(RenderingContextSharedPtr renderingContext);

	uint32_t getFPS() const;
	uint32_t getTargetFPS() const;
	double getDeltaTime() const;
	const rendell_ui::ViewportSharedPtr getViewport() const;
	const RenderingContextSharedPtr getRenderingContext() const;

private:
	void cooldown(double sleepTime);
	void onRefreshed() override;

	uint32_t _fps{ 0 };
	uint32_t _targetFps{ 60 };
	double _targetFrameTime{ 1.0 / _targetFps };

	TimePoint _frameStartTimePoint{};
	TimePoint _frameEndTimePoint{};
	double _deltaTime{};

	rendell_ui::ViewportSharedPtr _viewport{ nullptr };
	RenderingContextSharedPtr _renderingContext{ nullptr };
};

typedef std::unique_ptr<RenderingWindow> RenderingWindowUniquePtr;
typedef std::shared_ptr<RenderingWindow> RenderingWindowSharedPtr;
