#include "CodeEditorWidget.h"

CodeEditorWidget::CodeEditorWidget()
{
	_textEditorWidget = rendell_ui::createTextEditWidget();
}

void CodeEditorWidget::onSelfWeakPtrChanged()
{
	if (_textEditorWidget)
	{
		_textEditorWidget->setParent(_selfWeakPtr);
	}
}

