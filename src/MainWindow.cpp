#include "MainWindow.h"
#include "Viewport.h"
#include <glm/gtc/matrix_transform.hpp>

RenderingWindow::RenderingWindow(int width, int height, const char* title) :
	Window(width, height, title)
{

}

void RenderingWindow::update()
{
	_viewport->apply();
	_renderingContext->render();

	swapBuffers();
}

void RenderingWindow::setViewport(ViewportSharedPtr viewport)
{
	_viewport = viewport;
}

void RenderingWindow::setRenderingContext(RenderingContextSharedPtr renderingContext)
{
	_renderingContext = renderingContext;
}

const ViewportSharedPtr RenderingWindow::getViewport() const
{
	return _viewport;
}

const RenderingContextSharedPtr RenderingWindow::getRenderingContext() const
{
	return _renderingContext;
}

void RenderingWindow::onRefreshed()
{
	const glm::ivec2 size = getSize();
	const int width = size.x, height = size.y;

	const float ratio = (float)width / (float)height;
	const float worldWidth = height * ratio;

	const float halfWidth = worldWidth * 0.5f;
	const float halfHeight = height * 0.5f;

	const glm::mat4 projectMat = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0f, 1.0f);
	_viewport->setProjectMat(projectMat);
	_viewport->setParameters(0, 0, width, height);

	update();
}
