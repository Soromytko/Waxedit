#include <View/Widgets/CodeEditorWidget.h>

#define MARGIN 50.0f

CodeEditorWidget::CodeEditorWidget() {
    setName("CodeEditorWidget");
    _textEditorWidget = rendell_ui::createTextEditWidget();
    _textEditorWidget->setAnchor(rendell_ui::Anchor::centerStretch);
    _textEditorWidget->setMargins(rendell_ui::Margins{MARGIN, 0.0f, 0.0f, 0.0f});
    _textChangedConnectionId =
        _textEditorWidget->textChanged.connect(this, &CodeEditorWidget::onTextChanged);
    _scrollProgressChangedConnectionId = _textEditorWidget->scrollProgressChanged.connect(
        this, &CodeEditorWidget::onScrollProgressChanged);

    _lineNumberingWidget = createUnregisteredLineNumberingWidget();
    _lineNumberingWidget->setInteract(false);
    _lineNumberingWidget->setAnchor(rendell_ui::Anchor::leftStretch);
    _lineNumberingWidget->setSize({MARGIN, 0.0f});
}

CodeEditorWidget::~CodeEditorWidget() {
    _textEditorWidget->textChanged.disconnect(_textChangedConnectionId);
}

void CodeEditorWidget::draw() {
    _lineNumberingWidget->draw();
}

const std::wstring &CodeEditorWidget::getText() const {
    return _textEditorWidget->getText();
}

void CodeEditorWidget::setText(const std::wstring &value) {
    _textEditorWidget->setText(value);
}

void CodeEditorWidget::onSelfWeakPtrChanged() {
    if (_textEditorWidget) {
        _textEditorWidget->setParent(_selfWeakPtr);
    }
    if (_lineNumberingWidget) {
        _lineNumberingWidget->setParent(_selfWeakPtr);
    }
}

void CodeEditorWidget::onTextChanged() {
    const size_t lineCount = _textEditorWidget->getLineCount();
    _lineNumberingWidget->setLineCount(lineCount);
}

void CodeEditorWidget::onScrollProgressChanged(double scrollProgress) {
    _lineNumberingWidget->setScrollProgress(scrollProgress);
}
