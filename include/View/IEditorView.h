#pragma once
#include <memory>
#include <string>

class IEditorView
{
protected:
	IEditorView() = default;

public:
	~IEditorView() = default;

	virtual const std::wstring& getDocumentContent(const std::wstring& name) const = 0;
	virtual void addDocument(const std::wstring& name, const std::wstring& text) = 0;
	virtual void removeDocument(const std::wstring& name) = 0;

};

typedef std::weak_ptr<IEditorView> IEditorViewWeakPtr;
