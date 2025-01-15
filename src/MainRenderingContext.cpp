#include "MainRenderingContext.h"
#include "Widgets/Rectangle.h"
#include "Widgets/Text.h"
#include "Shaders/ShaderStorage.h"

#define FONT_WIDTH 32.0f
#define FONT_HEIGHT 32.0f
#define BACKGROUND_COLOR 31.0f / 255.0

MainRenderingContext::MainRenderingContext() : IRenderingContext()
{
	ShaderStorage::init();

	rendell::setClearBits(rendell::colorBufferBit | rendell::depthBufferBit);

	Rectangle* rectangle = new Rectangle();
	rectangle->getTransform().setScale(glm::vec2(50.0f, 50.0f));
	rectangle->setColor(glm::vec4(1.0f, 0.7f, 0.5f, 1.0f));

	Text* text = new Text();
	text->setText(L"Hello World!");
	text->setFontPath("../res/Fonts/mononoki/mononoki-Regular.ttf");
	text->setFontSize(glm::vec2(FONT_WIDTH, FONT_HEIGHT));
	text->setBackgroundColor(glm::vec4(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1.0f));
	text->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	text->getTransform().setPosition(glm::vec2(-100.0f, -100.0f));

	_widgets.push_back(WidgetSharedPtr(rectangle));
	_widgets.push_back(WidgetSharedPtr(text));
}

MainRenderingContext::~MainRenderingContext()
{
	ShaderStorage::release();
}

void MainRenderingContext::setViewport(int x, int y, int width, int height)
{
	rendell::setViewport(x, y, width, height);
}

void MainRenderingContext::render() const
{
	rendell::clear();
	rendell::clearColor(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1);

	for (const WidgetSharedPtr& widget : _widgets)
	{
		widget->draw();
	}

}
