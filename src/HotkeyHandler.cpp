#include "HotkeyHandler.h"

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

void HotkeyHandler::handleCtrlHotkeys(rendell_ui::InputKey key)
{
	switch (key)
	{
	case rendell_ui::InputKey::O:
	{
		std::cout << "Hotkey inputted: Ctrl + O" << std::endl;
		break;
	}
	case rendell_ui::InputKey::S:
	{
		std::cout << "Hotkey inputted: Ctrl + S" << std::endl;
		break;
	}
	}
}

void HotkeyHandler::handleCtrlShiftHotkeys(rendell_ui::InputKey key)
{
}
