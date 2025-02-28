#pragma once
#include <memory>
#include <rendell_ui/rendell_ui.h>

class HotkeyHandler
{
public:
	void handle(const rendell_ui::KeyboardInput& keyboardInput);

private:
	void handleCtrlHotkeys(rendell_ui::InputKey key);
	void handleCtrlShiftHotkeys(rendell_ui::InputKey key);

};

typedef std::shared_ptr<HotkeyHandler> HotkeyHandlerSharedPtr;
