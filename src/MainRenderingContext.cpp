#include "MainRenderingContext.h"
#include "Widgets/Rectangle.h"
#include "Widgets/Text.h"
#include "Shaders/ShaderStorage.h"
#include "Widgets/rendell_widget.h"

#define FONT_WIDTH 32.0f
#define FONT_HEIGHT 32.0f
#define BACKGROUND_COLOR 31.0f / 255.0

MainRenderingContext::MainRenderingContext() : IRenderingContext()
{
	ShaderStorage::init();

	rendell::setClearBits(rendell::colorBufferBit | rendell::depthBufferBit);

	_rootWidget = std::make_shared<Widget>();
	_rootWidget->setAnchor(Anchor::middleStretch);

	Rectangle* rectangle = new Rectangle(_rootWidget.get());
	rectangle->setColor(glm::vec4(1.0f, 0.7f, 0.5f, 1.0f));
	rectangle->setMargins(30, 100, 20, 0);
	rectangle->setAnchor(Anchor::topStretch);

	Rectangle* redRectangle = new Rectangle(rectangle);
	redRectangle->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	redRectangle->setSize(glm::vec2(50.0f, 50.0f));
	redRectangle->setAnchor(Anchor::rightBottom);
	redRectangle->setMargins(0, 10, 20, 0);

	Text* text = new Text(_rootWidget.get());
	text->setText(L"Hello World!");
	text->setFontPath("../res/Fonts/mononoki/mononoki-Regular.ttf");
	text->setFontSize(glm::vec2(FONT_WIDTH, FONT_HEIGHT));
	text->setBackgroundColor(glm::vec4(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1.0f));
	text->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	text->setOffset(glm::vec2(-100.0f, -100.0f));
	text->setAnchor(Anchor::center);

}

MainRenderingContext::~MainRenderingContext()
{
	ShaderStorage::release();
}

void MainRenderingContext::render() const
{
	rendell::clear();
	rendell::clearColor(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1);

	rendell_widget::draw();
}

void MainRenderingContext::onViewportUpdated(int x, int y, int width, int height)
{
	_rootWidget->updateRecursively();
}
