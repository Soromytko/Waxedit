#pragma once
#include <memory>

class IRenderingContext
{
protected:
	IRenderingContext() = default;

public:
	virtual ~IRenderingContext() = default;

	virtual void render() const = 0;
	virtual void onViewportUpdated(int x, int y, int width, int height) = 0;

};

typedef std::shared_ptr<IRenderingContext> RenderingContextSharedPtr;