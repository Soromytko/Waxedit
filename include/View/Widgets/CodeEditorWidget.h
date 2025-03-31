#pragma once
#include <rendell_ui/rendell_ui.h>
#include <View/Widgets/LineNumberingWidget.h>

class CodeEditorWidget final : public rendell_ui::Widget
{
public:
	CodeEditorWidget();
	~CodeEditorWidget();

	void draw() const override;

	const std::wstring& getText() const;

	void setText(const std::wstring& value);

private:
	void onSelfWeakPtrChanged() override;

	void onTextChanged();
	void onScrollProgressChanged(float scrollProgress);

	rendell_ui::TextEditWidgetSharedPtr _textEditorWidget;
	LineNumberingWidgetSharedPtr _lineNumberingWidget;

	uint32_t _textChangedConnectionId;
	uint32_t _scrollProgressChangedConnectionId;
	size_t _prevLineCount{ 0 };
};

RENDELL_UI_DECLARE_WIDGET(CodeEditorWidget)