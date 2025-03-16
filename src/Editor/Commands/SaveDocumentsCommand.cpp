#include "SaveDocumentsCommand.h"
#include "../Editor.h"

bool SaveDocumentsCommand::execute()
{
	return Editor::getInstance()->saveAllDocuments();
}