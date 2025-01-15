#pragma once
#include <memory>

class IRenderingContext
{
protected:
	IRenderingContext() = default;

public:
	virtual ~IRenderingContext() = default;

	virtual void setViewport(int x, int y, int width, int height) = 0;
	virtual void render() const = 0;

};

typedef std::shared_ptr<IRenderingContext> RenderingContextSharedPtr;