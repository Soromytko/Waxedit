#pragma once
#include <rendell_ui/rendell_ui.h>

class CodeEditorWidget : public rendell_ui::Widget
{
	RENDELL_UI_FRIEND_WIDGET
private:
	CodeEditorWidget();

public:
	~CodeEditorWidget() = default;

private:
	void onSelfWeakPtrChanged() override;

	rendell_ui::TextEditWidgetSharedPtr _textEditorWidget;
	//rendell_ui::TextEditWidgetSharedPtr _lineNumbersWidget;
};

RENDELL_UI_DECLARE_WIDGET(CodeEditorWidget)