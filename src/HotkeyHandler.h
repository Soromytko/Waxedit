#pragma once
#include <memory>
#include <rendell_ui/rendell_ui.h>
#include "Editor/Commands/Invoker.h"
#include "defines.h"

class HotkeyHandler
{
public:
	void handle(const rendell_ui::KeyboardInput& keyboardInput);
	void setInvoker(InvokerSharedPtr invoker);

private:
	void handleCtrlHotkeys(rendell_ui::InputKey key);
	void handleCtrlShiftHotkeys(rendell_ui::InputKey key);

	InvokerSharedPtr _invoker{ nullptr };

};

DECLARE_SHARED_PTR_FACTORY(HotkeyHandler)
