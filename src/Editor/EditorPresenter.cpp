#include "EditorPresenter.h"

IEditorViewWeakPtr EditorPresenter::getView() const
{
	return _view;
}

EditorModelSharedPtr EditorPresenter::getModel() const
{
	return _model;
}

void EditorPresenter::setView(IEditorViewWeakPtr view)
{
	_view = view;
}

void EditorPresenter::setModel(EditorModelSharedPtr model)
{
	_model = model;
}

bool EditorPresenter::loadDocument(const std::filesystem::path& path)
{
	return _model->loadDocument(path);
}

void EditorPresenter::onDocumentAdded(const std::wstring& name, const std::wstring& content)
{
	if (auto view = _view.lock())
	{
		view->addDocument(name, content);
	}
}

void EditorPresenter::onDocumentRemoved(const std::wstring& name)
{
}
