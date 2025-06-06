#include <View/Widgets/LineNumberingWidget.h>
#include <rendell_ui/Viewport.h>

void LineNumberingWidget::draw() const
{
	const glm::mat4& projectMat = rendell_ui::Viewport::getCurrent()->getProjectMat();
	const glm::mat4& viewMat = rendell_ui::Viewport::getCurrent()->getViewMat();
	const glm::mat4& transformMat = _transform.getMatrix();

	_textDrawer.draw(projectMat * viewMat, transformMat);
}

double LineNumberingWidget::getScrollProgress() const
{
	return _textDrawer.getScrollProgress();
}

glm::vec2 LineNumberingWidget::getFontSize() const
{
	return _fontSize;
}

void LineNumberingWidget::setFontSize(glm::ivec2 value)
{
	if (_fontSize != value)
	{
		_fontSize = value;

		// TODO: There needs to be a better way to do this.
		for (const rendell_text::TextRendererSharedPtr& line : _textDrawer.getLines())
		{
			line->getTextLayout()->setFontSize(_fontSize);
		}
	}
}

void LineNumberingWidget::setScrollProgress(double value)
{
	_textDrawer.setScrollProgress(value);
}

static rendell_text::TextLayoutSharedPtr createTextLayout(std::wstring&& text, glm::ivec2 fontSize)
{
	const std::filesystem::path fontPath = std::filesystem::path(FONT_ROOT_DIRECTORY) / "mononoki/mononoki-Regular.ttf";
	rendell_text::TextLayoutSharedPtr result = rendell_text::makeTextLayout();
	result->setText(std::move(text));
	result->setFontPath(fontPath);
	result->setFontSize(fontSize);
	return result;
}

static rendell_text::TextRendererSharedPtr createLineNumberTextRenderer(size_t lineNumber, glm::ivec2 fontSize)
{
	rendell_text::TextRendererSharedPtr result = rendell_text::makeTextRenderer();
	rendell_text::TextLayoutSharedPtr textLayout = createTextLayout(std::to_wstring(lineNumber), fontSize);
	result->setTextLayout(textLayout);
	result->setBackgroundColor(glm::vec4(31.0f / 255.0, 31.0f / 255.0, 31.0f / 255.0, 1.0f));
	result->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	return result;
}

void LineNumberingWidget::setLineCount(size_t value)
{
	if (_lineCount != value)
	{
		if (_lineCount > value)
		{
			for (size_t i = 0; i < _lineCount - value; i++)
			{
				_textDrawer.removeLine(_textDrawer.getLines().size() - 1);
			}
		}
		else
		{
			for (size_t i = 0; i < value - _lineCount; i++)
			{
				const size_t index = _textDrawer.getLines().size();
				const rendell_text::TextRendererSharedPtr textRenderer = createLineNumberTextRenderer(index + 1, _fontSize);
				_textDrawer.addLine(index, textRenderer);
			}
		}
		_lineCount = value;
	}
}

void LineNumberingWidget::onSizeChanged()
{
	_textDrawer.setSize(_size);
}
