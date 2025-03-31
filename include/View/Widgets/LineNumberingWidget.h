#pragma once
#include <rendell_ui/rendell_ui.h>
#include <rendell_ui/Widgets/private/TextDrawer.h>

class LineNumberingWidget final : public rendell_ui::Widget
{
public:
	LineNumberingWidget() = default;
	~LineNumberingWidget() = default;

	void draw() const override;
	float getScrollProgress() const;
	glm::vec2 getFontSize() const;

	void setFontSize(glm::ivec2 value);
	void setScrollProgress(float value);
	void setLineCount(size_t value);

private:
	void onSizeChanged() override;

	rendell_ui::TextDrawer _textDrawer{};
	glm::ivec2 _fontSize{ 24, 24 };
	size_t _lineCount{};
};

RENDELL_UI_DECLARE_WIDGET(LineNumberingWidget)
