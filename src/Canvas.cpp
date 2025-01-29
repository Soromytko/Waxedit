#include "Canvas.h"

Canvas::Canvas(rendell_ui::ViewportSharedPtr viewport) : rendell_ui::Canvas(viewport)
{

}

void Canvas::onRefreshed(int width, int height)
{
	rendell_ui::Canvas::onRefreshed(width, height);
	if (_refreshedCallback)
	{
		_refreshedCallback(width, height);
	}
}

void Canvas::setRefreshedCallback(RefreshedCallback callback)
{
	_refreshedCallback = callback;
}

