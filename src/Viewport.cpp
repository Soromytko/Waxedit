#include "Viewport.h"

static ViewportSharedPtr s_currentViewport{ nullptr };

void Viewport::setCurrent(const ViewportSharedPtr viewport)
{
	s_currentViewport = viewport;
}

ViewportSharedPtr Viewport::getCurrent()
{
	return s_currentViewport;
}

void Viewport::setProjectMat(const glm::mat4& value)
{
	_projectMat = value;
}

void Viewport::setViewMat(const glm::mat4& value)
{
	_viewMat = value;
}

const glm::mat4& Viewport::getProjectMat() const
{
	return _projectMat;
}

const glm::mat4& Viewport::getVewMat() const
{
	return _viewMat;
}
