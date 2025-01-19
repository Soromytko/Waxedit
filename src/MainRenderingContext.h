#pragma once
#include <memory>
#include "IRenderingContext.h"
#include "Widgets/Widget.h"

class MainRenderingContext final : public IRenderingContext
{
public:
	MainRenderingContext();
	~MainRenderingContext();

	void render() const override;
	void onViewportUpdated(int x, int y, int width, int height) override;

private:
	void drawWidgets(Widget* rootWidget) const;

	WidgetSharedPtr _rootWidget{ nullptr };
	std::vector<Widget*> _widgets;

};