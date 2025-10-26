#pragma once
#include "Document.h"
#include "EditorModelObserver.h"
#include "defines.h"
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <vector>

class EditorModel final {
public:
    EditorModel() = default;
    ~EditorModel() = default;

    const std::vector<std::wstring> &getDocumentNames() const;

    void setObserver(EditorModelObserverWeakPtr observer);
    void setDocumentContent(const std::wstring &name, const std::wstring &content);

    bool loadDocument(const std::filesystem::path &path);
    bool saveDocuments();

private:
    EditorModelObserverWeakPtr _observer;
    std::unordered_map<std::wstring, DocumentSharedPtr> _documents;
    std::vector<std::wstring> _documentNames;
};

DECLARE_SHARED_PTR_FACTORY(EditorModel)
