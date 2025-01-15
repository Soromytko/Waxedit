#pragma once
#include <memory>
#include "IRenderingContext.h"
#include "Widgets/Widget.h"

class MainRenderingContext final : public IRenderingContext
{
public:
	MainRenderingContext();
	~MainRenderingContext();

	void setViewport(int x, int y, int width, int height);
	void render() const override;

private:
	std::vector<WidgetSharedPtr> _widgets;

};