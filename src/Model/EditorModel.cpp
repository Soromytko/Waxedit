#include <Model/EditorModel.h>
#include <iostream>

const std::vector<std::wstring> &EditorModel::getDocumentNames() const {
    return _documentNames;
}

void EditorModel::setObserver(EditorModelObserverWeakPtr observer) {
    _observer = observer;
}

void EditorModel::setDocumentContent(const std::wstring &name, const std::wstring &content) {
    auto it = _documents.find(name);
    if (it == _documents.end()) {
        return;
    }
    std::wstring documentContent = content;
    it->second->setContent(std::move(documentContent));
}

bool EditorModel::loadDocument(const std::filesystem::path &path) {
    const std::wstring &documentName = path.filename().wstring();
    if (_documents.find(documentName) != _documents.end()) {
        std::cout << "LOG::EditorModel: This file is already open " << path << std::endl;
        return false;
    }

    DocumentSharedPtr document = makeDocument(documentName, path);
    if (!document->isLoaded()) {
        std::cout << "ERROR::EditorModel: Failed to read file " << path << std::endl;
        return false;
    }

    _documents.insert({documentName, document});
    _documentNames.push_back(documentName);

    if (auto observer = _observer.lock()) {
        observer->onDocumentAdded(document->getName(), document->getContent());
    }

    return true;
}

bool EditorModel::saveDocuments() {
    if (_documents.size() == 0) {
        return false;
    }

    bool result = true;
    for (auto it = _documents.begin(); it != _documents.end(); it++) {
        const bool isSaved = it->second->save();
        result = result && isSaved;
    }
    return result;
}
