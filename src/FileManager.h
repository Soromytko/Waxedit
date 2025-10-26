#pragma once
#include <memory>

class FileManager {
public:
    bool saveOpenedFile();

    bool saveOpenedFileWithDialog();
    bool openFileWithDialog();
};

typedef std::shared_ptr<FileManager> FileManagerSharedPtr;
