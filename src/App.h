#pragma once
#include "Canvas.h"
#include "Editor/Commands/Invoker.h"
#include "HotkeyHandler.h"
#include "IRenderer.h"
#include <rendell_ui/rendell_ui.h>

class App final {
public:
    App();
    ~App();
    int run();

private:
    void setupViewport();

    int _result{0};

    IRendererSharedPtr _renderer;
    HotkeyHandlerSharedPtr _hotkeyHandler;

    rendell_ui::IWindow *_mainWindow;
    rendell_ui::ViewportSharedPtr _viewport;
    EditorCanvasSharedPtr _canvas;
    InvokerSharedPtr _invoker;
};