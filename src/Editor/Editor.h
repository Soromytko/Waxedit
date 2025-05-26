#pragma once
#include <map>
#include <filesystem>
#include <utility>
#include <Model/Document.h>
#include <View/EditorView.h>
#include "../Canvas.h"

class Editor final
{
private:
	Editor(EditorCanvasSharedPtr canvas);

public:
	~Editor() = default;

	EditorCanvasSharedPtr getCanvas() const;
	const std::wstring& getCurrentDocumentName() const;
	size_t getOpenedDocumentCount() const;

	static bool init(EditorCanvasSharedPtr canvas);
	static void release();
	static Editor* getInstance();

	bool openDocument(const std::filesystem::path& path);
	bool closeDocument(const std::wstring& name);
	bool saveAllDocuments();

private:
	EditorViewSharedPtr _view;
	EditorPresenterSharedPtr _presenter;

};
