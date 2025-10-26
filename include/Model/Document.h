#pragma once
#include "defines.h"
#include <filesystem>
#include <memory>
#include <string>

class Document final {
public:
    Document(const std::wstring &name, const std::filesystem::path &path);
    virtual ~Document() = default;

    bool isLoaded() const;
    const std::wstring &getName() const;
    const std::wstring &getContent() const;
    bool hasChanges() const;

    void setContent(std::wstring &&content);

    bool save();

private:
    bool loadFile(std::wstring &result);

    bool _isLoaded{false};
    std::filesystem::path _path;
    std::wstring _name;
    std::wstring _content;
};

DECLARE_SHARED_PTR_FACTORY(Document)
