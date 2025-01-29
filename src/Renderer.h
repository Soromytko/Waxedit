#pragma once
#include <memory>
#include <rendell_ui/rendell_ui.h>
#include "IRenderer.h"

class MainRenderingContext final : public IRenderingContext
{
public:
	MainRenderingContext();
	~MainRenderingContext();

	void render() const override;
	void onViewportUpdated(int x, int y, int width, int height) override;

private:
	rendell_ui::WidgetSharedPtr _rootWidget{ nullptr };

};