#include "HotkeyHandler.h"
#include "Editor/Commands/OpenFileCommand.h"
#include "Editor/Commands/SaveDocumentsCommand.h"

void HotkeyHandler::handle(const rendell_ui::KeyboardInput& keyboardInput)
{
	if (keyboardInput.action == rendell_ui::InputAction::pressed)
	{
		if (keyboardInput.modControl.hasCtrlMod())
		{
			if (keyboardInput.modControl.hasShiftMod())
			{
				handleCtrlShiftHotkeys(keyboardInput.key);
			}
			else
			{
				handleCtrlHotkeys(keyboardInput.key);
			}
		}
	}
}

void HotkeyHandler::setInvoker(InvokerSharedPtr invoker)
{
	_invoker = invoker;
}

void HotkeyHandler::handleCtrlHotkeys(rendell_ui::InputKey key)
{
	switch (key)
	{
	case rendell_ui::InputKey::O:
	{
		_invoker->executeCommand(makeOpenFileCommand());
		break;
	}
	case rendell_ui::InputKey::S:
	{
		_invoker->executeCommand(makeSaveDocumentsCommand());
		break;
	}
	}
}

void HotkeyHandler::handleCtrlShiftHotkeys(rendell_ui::InputKey key)
{
}
