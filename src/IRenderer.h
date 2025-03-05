#pragma once
#include <memory>
#include "defines.h"

class IRenderer
{
protected:
	IRenderer() = default;

public:
	virtual ~IRenderer() = default;

	virtual void startFrame() = 0;
	virtual void endFrame() = 0;
	virtual void cooldown() = 0;
	virtual void render() const = 0;

};

DECLARE_SHARED_PTR(IRenderer)
