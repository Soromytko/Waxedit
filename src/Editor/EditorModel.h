#pragma once
#include <memory>
#include <unordered_map>
#include <filesystem>
#include "../defines.h"
#include "EditorModelObserver.h"
#include "Document.h"

class EditorModel final
{
public:
	EditorModel() = default;
	~EditorModel() = default;

	void setObserver(EditorModelObserverWeakPtr observer);

	bool loadDocument(const std::filesystem::path& path);

private:
	EditorModelObserverWeakPtr _observer;
	std::unordered_map<std::wstring, DocumentSharedPtr> _documents;
};

typedef std::shared_ptr<EditorModel> EditorModelSharedPtr;

template <typename... Args>
EditorModelSharedPtr makeEditorModel(Args&&... args)
{
	return std::make_shared<EditorModel>(std::forward<Args>(args)...);
}
