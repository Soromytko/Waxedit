#include "Editor.h"
#include <iostream>
#include <cassert>
#include <fstream>

static Editor* s_instance{ nullptr };

Editor::Editor(EditorCanvasSharedPtr canvas)
{
	EditorModelSharedPtr model = makeEditorModel();
	EditorPresenterSharedPtr presenter = makeEditorPresenter();
	EditorViewSharedPtr view = makeEditorView(canvas);

	model->setObserver(presenter);

	presenter->setModel(model);
	presenter->setView(view);

	view->setPresenter(presenter);

	_view = view;
	_presenter = presenter;
}

EditorCanvasSharedPtr Editor::getCanvas() const
{
	return _view->getCanvas();
}

bool Editor::init(EditorCanvasSharedPtr canvas)
{
	assert(s_instance == nullptr);
	s_instance = new Editor(canvas);
	return true;
}

void Editor::release()
{
	assert(s_instance != nullptr);
	delete s_instance;
	s_instance = nullptr;
}

Editor* Editor::getInstance()
{
	assert(s_instance != nullptr);
	return s_instance;
}

bool Editor::openDocument(const std::filesystem::path& path)
{
	if (path.empty())
	{
		std::cout << "ERROR::Editor: Path is empty" << std::endl;
		return false;
	}

	return _presenter->loadDocument(path);;
}

bool Editor::closeDocument(const std::string& name)
{
	return false;
}

bool Editor::saveAllDocuments()
{
	_presenter->updateDocuments();
	return _presenter->saveAllDocuments();
}
