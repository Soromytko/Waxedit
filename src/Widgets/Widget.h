#pragma once
#include <memory>
#include <rendell/rendell.h>
#include "Transform2D.h"

class Widget
{
protected:
	Widget() = default;

public:
	~Widget() = default;

	void setTransform(const Transform2D& value);
	Transform2D& getTransform();
	const Transform2D& getTransform() const;

	virtual void setColor(glm::vec4 value);
	glm::vec4 getColor() const;

	virtual void draw() const = 0;

protected:
	virtual void updateUniforms() const;

	uint32_t _matrixUniformIndex{ 0 };
	uint32_t _colorUniformIndex{ 0 };

	Transform2D _transform{};
	glm::vec4 _color{ 1.0f, 1.0f, 1.0f, 1.0f };
	rendell::ShaderProgramSharedPtr _shaderProgram{ nullptr };

};

typedef std::shared_ptr<Widget> WidgetSharedPtr;
