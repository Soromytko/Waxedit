#pragma once
#include <map>
#include <filesystem>
#include <utility>
#include "Document.h"
#include "../Canvas.h"
#include "EditorView.h"

class Editor final
{
private:
	Editor(EditorCanvasSharedPtr canvas);

public:
	~Editor() = default;

	EditorCanvasSharedPtr getCanvas() const;

	static bool init(EditorCanvasSharedPtr canvas);
	static void release();
	static Editor* getInstance();

	bool openDocument(const std::filesystem::path& path);
	bool closeDocument(const std::string& name);

private:
	EditorViewSharedPtr _view;
	EditorPresenterSharedPtr _presenter;

};
