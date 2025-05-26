#pragma once
#include <memory>
#include <string>

class IEditorView
{
protected:
	IEditorView() = default;

public:
	~IEditorView() = default;

	virtual size_t getDocumentCount() const = 0;
	virtual const std::wstring& getCurrentDocumentName() const = 0;
	virtual const std::wstring& getDocumentContent(const std::wstring& name) const = 0;
	virtual void addDocument(const std::wstring& name, const std::wstring& text) = 0;
	virtual bool removeDocument(const std::wstring& name) = 0;

};

typedef std::weak_ptr<IEditorView> IEditorViewWeakPtr;
