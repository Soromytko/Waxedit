#pragma once
#include <memory>
#include <string>
#include <filesystem>

class EditorModelObserver
{
protected:
	EditorModelObserver() = default;

public:
	virtual void onDocumentAdded(const std::wstring& name, const std::wstring& content) {};
	virtual void onDocumentRemoved(const std::wstring& name) {};

public:
	virtual ~EditorModelObserver() = default;

};

typedef std::weak_ptr<EditorModelObserver> EditorModelObserverWeakPtr;
