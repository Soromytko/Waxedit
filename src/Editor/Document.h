#pragma once
#include <memory>
#include <string>
#include <filesystem>

class Document final
{
public:
	Document(const std::wstring& name, const std::filesystem::path& path);
	virtual ~Document() = default;

	bool isLoaded() const;
	const std::wstring& getName() const;
	const std::wstring& getContent() const;
	bool hasChanges() const;

	bool save();

private:
	bool loadFile(std::wstring& result);

	bool _isLoaded{ false };
	std::filesystem::path _path;
	std::wstring _name;
	std::wstring _content;

};

typedef std::shared_ptr<Document> DocumentSharedPtr;

template <typename... Args>
DocumentSharedPtr makeDocument(Args&&... args)
{
	return std::make_shared<Document>(std::forward<Args>(args)...);
}

