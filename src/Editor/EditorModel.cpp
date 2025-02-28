#include "EditorModel.h"
#include <iostream>

void EditorModel::setObserver(EditorModelObserverWeakPtr observer)
{
	_observer = observer;
}

bool EditorModel::loadDocument(const std::filesystem::path& path)
{
	const std::wstring& documentName = path.filename().wstring();
	if (_documents.find(documentName) != _documents.end())
	{
		std::cout << "LOG::EditorModel: This file is already open " << path << std::endl;
		return false;
	}

	DocumentSharedPtr document = makeDocument(documentName, path);
	if (!document->isLoaded())
	{
		std::cout << "ERROR::EditorModel: Failed to read file " << path << std::endl;
		return false;
	}

	_documents.insert({ documentName, document });
	
	if (auto observer = _observer.lock())
	{
		observer->onDocumentAdded(document->getName(), document->getContent());
	}

	return true;
}
