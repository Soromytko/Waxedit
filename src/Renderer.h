#pragma once
#include <memory>
#include <rendell_ui/rendell_ui.h>
#include "IRenderer.h"

class Renderer final : public IRenderer
{
public:
	Renderer();
	~Renderer();

	void render() const override;
	void onViewportUpdated(int x, int y, int width, int height) override;

private:
	rendell_ui::WidgetSharedPtr _rootWidget{ nullptr };

};