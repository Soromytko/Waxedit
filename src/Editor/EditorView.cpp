#include "EditorView.h"

#define FONT_WIDTH 32.0f
#define FONT_HEIGHT 32.0f
#define BACKGROUND_COLOR 31.0f / 255.0

EditorView::EditorView(EditorCanvasSharedPtr canvas) :
	_canvas(canvas), _presenter(nullptr)
{
	_rootWidget = rendell_ui::makeRectangleWidget();
	_rootWidget->setColor(glm::vec4(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1.0f));
	_rootWidget->setAnchor(rendell_ui::Anchor::centerStretch);
	_canvas->addWidget(_rootWidget);
	addDocument(L"Some", LR"(#include <iostream>

int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}
	)");
	_canvas->focusWidget(_documents.begin()->second);
}

EditorCanvasSharedPtr EditorView::getCanvas() const
{
	return _canvas;
}

EditorPresenterSharedPtr EditorView::getPresenter() const
{
	return _presenter;
}

void EditorView::setPresenter(EditorPresenterSharedPtr presenter)
{
	_presenter = presenter;
}

void EditorView::addDocument(const std::wstring& name, const std::wstring& text)
{
	if (_documents.find(name) != _documents.end())
	{
		return;
	}

	// TODO: Load data into the first document.
	if (!_documents.empty())
	{
		rendell_ui::TextEditWidget* textWidget = _documents.begin()->second;
		textWidget->setText(text);
		return;
	}

	rendell_ui::TextEditWidget* document = createTextEdit(_rootWidget.get(), text);
	_documents.insert({ name, document });
}

void EditorView::removeDocument(const std::wstring& name)
{
	auto it = _documents.find(name);
	if (it == _documents.end())
	{
		return;
	}

	delete it->second;
	_documents.erase(name);
}

rendell_ui::TextEditWidget* EditorView::createTextEdit(rendell_ui::Widget* parent, const std::wstring& text) const
{
	rendell_ui::TextEditWidget* result = new rendell_ui::TextEditWidget(parent);
	result->setAnchor(rendell_ui::Anchor::centerStretch);
	result->setText(text);
	return result;
}
