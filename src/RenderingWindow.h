#pragma once
#include <rendell_ui/rendell_ui.h>
#include "IRenderingContext.h"
#include <memory>

class RenderingWindow final : public rendell_ui::Window
{
public:
	RenderingWindow(int width, int height, const char* title);
	~RenderingWindow() = default;

	void update();

	void setViewport(rendell_ui::ViewportSharedPtr viewport);
	void setRenderingContext(RenderingContextSharedPtr renderingContext);

	const rendell_ui::ViewportSharedPtr getViewport() const;
	const RenderingContextSharedPtr getRenderingContext() const;

private:
	void onRefreshed() override;

	rendell_ui::ViewportSharedPtr _viewport{ nullptr };
	RenderingContextSharedPtr _renderingContext{ nullptr };
};

typedef std::unique_ptr<RenderingWindow> RenderingWindowUniquePtr;
typedef std::shared_ptr<RenderingWindow> RenderingWindowSharedPtr;
