#pragma once
#include <memory>

class IRenderingContext
{
protected:
	IRenderingContext() = default;

public:
	virtual ~IRenderingContext() = default;

	virtual void render() const = 0;

};

typedef std::shared_ptr<IRenderingContext> RenderingContextSharedPtr;