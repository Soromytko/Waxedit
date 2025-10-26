#include "Canvas.h"

EditorCanvas::EditorCanvas(rendell_ui::ViewportSharedPtr viewport)
    : rendell_ui::Canvas(viewport) {
}

void EditorCanvas::onRefreshed(int width, int height) {
    rendell_ui::Canvas::onRefreshed(width, height);
    if (_refreshedCallback) {
        _refreshedCallback(width, height);
    }
}

void EditorCanvas::onKeyInputted(const rendell_ui::KeyboardInput &keyboardInput) {
    _hotkeyHandler->handle(keyboardInput);

    rendell_ui::Canvas::onKeyInputted(keyboardInput);
}

void EditorCanvas::setHotkeyHandler(HotkeyHandlerSharedPtr hotkeyHandler) {
    _hotkeyHandler = hotkeyHandler;
}

void EditorCanvas::setRefreshedCallback(RefreshedCallback callback) {
    _refreshedCallback = callback;
}
