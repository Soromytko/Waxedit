#include <file_dialog.h>
#include <iostream>
#include <Windows.h>

std::string openFileDialog(const std::string& title, const std::string& filters)
{
	std::string result;

	OPENFILENAME ofn;
	char szFile[260] = { 0 };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	// e.g., "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0"
	ofn.lpstrFilter = filters.c_str();
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	ofn.lpstrTitle = title.c_str();

	if (GetOpenFileName(&ofn) == TRUE)
	{
		result = ofn.lpstrFile;
	}
	else
	{
		DWORD error = CommDlgExtendedError();
		if (error != 0)
		{
			std::cerr << "Open File Dialog Error: " << error << std::endl;
		}
	}

	return result;
}
