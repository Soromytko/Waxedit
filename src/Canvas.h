#pragma once
#include <memory>
#include <functional>
#include <rendell_ui/rendell_ui.h>
#include <defines.h>
#include "HotkeyHandler.h"

class EditorCanvas;

typedef std::function<void(int, int)> RefreshedCallback;

class EditorCanvas final : public rendell_ui::Canvas
{
public:
	EditorCanvas(rendell_ui::ViewportSharedPtr viewport);
	~EditorCanvas() = default;

	void onRefreshed(int width, int height) override;
	void onKeyInputted(const rendell_ui::KeyboardInput& keyboardInput) override;

	void setHotkeyHandler(HotkeyHandlerSharedPtr hotkeyHandler);
	void setRefreshedCallback(RefreshedCallback callback);

private:

	HotkeyHandlerSharedPtr _hotkeyHandler{ nullptr };
	RefreshedCallback _refreshedCallback{ nullptr };

};

DECLARE_SHARED_PTR_FACTORY(EditorCanvas)
