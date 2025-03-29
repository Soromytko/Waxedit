#include <Model/Document.h>
#include <iostream>
#include <fstream>
#include <cassert>

Document::Document(const std::wstring& name, const std::filesystem::path& path) :
	_name(name), _path(path)
{
	assert(!_path.empty());
	_isLoaded = loadFile(_content);
}

bool Document::isLoaded() const
{
	return _isLoaded;
}

const std::wstring& Document::getName() const
{
	return _name;
}

const std::wstring& Document::getContent() const
{
	return _content;
}

bool Document::hasChanges() const
{
	return false;
}

void Document::setContent(std::wstring&& content)
{
	_content = std::move(content);
}

bool Document::save()
{
	std::wofstream file(_path);
	if (!file.is_open())
	{
		return false;
	}
	file << _content;
	file.close();
	return true;
}

bool Document::loadFile(std::wstring& result)
{
	std::ifstream file(_path);

	if (!file.is_open())
	{
		return false;
	}

	const std::string rawResult((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	result = std::wstring(rawResult.begin(), rawResult.end());

	file.close();

	return true;
}
