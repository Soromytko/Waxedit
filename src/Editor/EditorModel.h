#pragma once
#include <memory>
#include <unordered_map>
#include <filesystem>
#include "EditorModelObserver.h"
#include "Document.h"
#include "../defines.h"

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

DECLARE_SHARED_PTR_FACTORY(EditorModel)
