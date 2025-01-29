#pragma once
#include <memory>
#include <functional>
#include <rendell_ui/rendell_ui.h>

class Canvas;

typedef std::function<void(int, int)> RefreshedCallback;
typedef std::shared_ptr<Canvas> CanvasSharedPtr;

class Canvas final : public rendell_ui::Canvas
{
public:
	Canvas(rendell_ui::ViewportSharedPtr viewport);
	~Canvas() = default;

	void onRefreshed(int width, int height) override;

	void setRefreshedCallback(RefreshedCallback callback);

private:
	RefreshedCallback _refreshedCallback{ nullptr };

};

