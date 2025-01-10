#include "Rectangle.h"
#include <cassert>
#include <array>
#include "../Viewport.h"
#include "../Shaders/ShaderStorage.h"

static const std::vector<float> s_vertices{
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,
};

static bool s_isUniformIndexObtained{ false };
static uint32_t s_matrixUniformIndex{ 0 };
static uint32_t s_colorUniformIndex{ 0 };

Rectangle::Rectangle() : Widget()
{
	_shaderProgram = ShaderStorage::getInstance()->rectangleShader->getShaderProgram();
	if (!s_isUniformIndexObtained)
	{
		s_matrixUniformIndex = _shaderProgram->getUniformIndex("u_Matrix");
		s_colorUniformIndex = _shaderProgram->getUniformIndex("u_Color");
		s_isUniformIndexObtained = true;
	}
	_matrixUniformIndex = s_matrixUniformIndex;
	_colorUniformIndex = s_colorUniformIndex;

	rendell::VertexBufferSharedPtr vertexBuffer = rendell::createVertexBuffer(s_vertices);
	vertexBuffer->setLayouts({ { rendell::ShaderDataType::float2, false, 0 } });
	_vertexArray = rendell::createVertexArray(nullptr, { vertexBuffer });
}

Rectangle::~Rectangle()
{

}

void Rectangle::draw() const
{
	updateUniforms();

	_vertexArray->bind();
	_shaderProgram->bind();

	rendell::drawTriangleStripArrays(0, 4);

	_shaderProgram->unbind();
	_vertexArray->unbind();
}
