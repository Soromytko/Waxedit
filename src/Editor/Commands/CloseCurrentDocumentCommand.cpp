#include "CloseCurrentDocumentCommand.h"
#include "../Editor.h"

bool CloseCurrentDocumentCommand::execute()
{
	Editor* editor = Editor::getInstance();
	if (editor->getOpenedDocumentCount() > 0)
	{
		const auto documentName = editor->getCurrentDocumentName();
		return editor->closeDocument(documentName);
	}

	return false;
}

