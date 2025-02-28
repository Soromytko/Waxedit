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
	Editor(CanvasSharedPtr canvas);

public:
	~Editor() = default;

	CanvasSharedPtr getCanvas() const;

	static bool init(CanvasSharedPtr canvas);
	static void release();
	static Editor* getInstance();

	bool openDocument(const std::filesystem::path& path);
	bool closeDocument(const std::string& name);

private:
	EditorViewSharedPtr _view;
	EditorPresenterSharedPtr _presenter;

};
