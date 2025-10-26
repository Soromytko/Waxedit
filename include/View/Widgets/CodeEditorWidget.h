#pragma once
#include <View/Widgets/LineNumberingWidget.h>
#include <rendell_ui/rendell_ui.h>

class CodeEditorWidget final : public rendell_ui::Widget {
public:
    CodeEditorWidget();
    ~CodeEditorWidget();

    void draw() override;

    const std::wstring &getText() const;

    void setText(const std::wstring &value);

private:
    void onSelfWeakPtrChanged() override;

    void onTextChanged();
    void onScrollProgressChanged(double scrollProgress);

    rendell_ui::TextEditWidgetSharedPtr _textEditorWidget;
    LineNumberingWidgetSharedPtr _lineNumberingWidget;

    rendell_ui::signal_connection_id_t _textChangedConnectionId;
    rendell_ui::signal_connection_id_t _scrollProgressChangedConnectionId;
    size_t _prevLineCount{0};
};

RENDELL_UI_DECLARE_WIDGET(CodeEditorWidget)