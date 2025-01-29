#pragma once
#include <memory>
#include <rendell_ui/rendell_ui.h>
#include "IRenderer.h"

class Renderer final : public IRenderer
{
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

public:
	Renderer(rendell_ui::ViewportSharedPtr viewport);
	~Renderer();

	void startFrame() override;
	void endFrame() override;
	void cooldown() override;
	void render() const override;

private:
	rendell_ui::ViewportSharedPtr _viewport;

	uint32_t _fps{ 0 };
	uint32_t _targetFps{ 60 };
	double _targetFrameTime{ 1.0 / _targetFps };

	TimePoint _frameStartTimePoint{};
	TimePoint _frameEndTimePoint{};
	double _deltaTime{};
	double _sleepTime{};

};