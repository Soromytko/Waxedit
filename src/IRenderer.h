#pragma once
#include "defines.h"
#include <memory>

class IRenderer {
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
