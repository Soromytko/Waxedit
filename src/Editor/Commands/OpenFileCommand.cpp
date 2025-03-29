#include "OpenFileCommand.h"
#include <file_dialog.h>
#include <iostream>
#include "../Editor.h"

bool OpenFileCommand::execute()
{
	const std::string& rawPath = openFileDialog("Select file", "");
	const std::filesystem::path path(rawPath);

	if (path.empty())
	{
		std::cout << "WARNING::OpenFileCommand: Path is empty" << std::endl;
		return false;
	}

	if (!Editor::getInstance()->openDocument(path))
	{
		std::cout << "WARNING::OpenFileCommand: Failed to open document " << path << std::endl;
		return false;
	}

	return false;
}