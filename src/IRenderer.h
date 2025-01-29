#pragma once
#include <memory>

class IRenderer
{
protected:
	IRenderer() = default;

public:
	virtual ~IRenderer() = default;

	virtual void render() const = 0;
	virtual void onViewportUpdated(int x, int y, int width, int height) = 0;

};

typedef std::shared_ptr<IRenderer> IRendererSharedPtr;