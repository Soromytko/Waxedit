#include "Widget.h"
#include "../Viewport.h"

void Widget::setTransform(const Transform2D& value)
{
	_transform = value;
}

Transform2D& Widget::getTransform()
{
	return _transform;
}

const Transform2D& Widget::getTransform() const
{
	return _transform;
}

void Widget::setColor(glm::vec4 value)
{
	_color = value;
}

glm::vec4 Widget::getColor() const
{
	return _color;
}

void Widget::updateUniforms() const
{
	const glm::mat4& projectMat = Viewport::getCurrent()->getProjectMat();
	const glm::mat4& viewMat = Viewport::getCurrent()->getViewMat();
	const glm::mat4& worldMat = _transform.getMatrix();
	const glm::mat4 mat = projectMat * viewMat * worldMat;

	_shaderProgram->setUniformMat4(
		_matrixUniformIndex,
		reinterpret_cast<const float*>(&mat)
	);

	_shaderProgram->setUniformVec4(_colorUniformIndex, reinterpret_cast<const float*>(&_color));
}
