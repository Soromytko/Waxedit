#include <View/EditorView.h>

#define FONT_WIDTH 32.0f
#define FONT_HEIGHT 32.0f
#define BACKGROUND_COLOR 31.0f / 255.0

#define HELLO_WORLD_SRC                                                                            \
    LR"(#include <iostream>

int main()
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}
)"

EditorView::EditorView(EditorCanvasSharedPtr canvas)
    : _canvas(canvas)
    , _presenter(nullptr) {
    _rootWidget = rendell_ui::createRectangleWidget(_canvas->getRootWidget());
    // auto rect = rendell_ui::createRectangleWidget(_rootWidget);
    // auto text = rendell_ui::createTextWidget(rect);
    // text->setText(HELLO_WORLD_SRC);
    // text->setColor({ 1.0f, 0.0f, 0.0f, 1.0f });
    // return;

    _rootWidget->setColor(glm::vec4(BACKGROUND_COLOR, BACKGROUND_COLOR, BACKGROUND_COLOR, 1.0f));
    _rootWidget->setAnchor(rendell_ui::Anchor::centerStretch);
    _rootWidget->setName("RootWidget");

    _pageViewer = rendell_ui::createPageViewerWidget(_rootWidget);
    _pageViewer->setAnchor(rendell_ui::Anchor::centerStretch);
    _tabBar = rendell_ui::createTabBarWidget(_rootWidget);
    _tabBar->currentIndexChanged.connect([&](int index) { _pageViewer->setCurrentIndex(index); });
    _pageViewer->setMargins(rendell_ui::Margins{0.0f, 0.0f, 0.0f, _tabBar->getSize().y});

    addDocument(L"New Document", HELLO_WORLD_SRC);

    _canvas->focusWidget(_documents.begin()->second);
}

EditorCanvasSharedPtr EditorView::getCanvas() const {
    return _canvas;
}

EditorPresenterSharedPtr EditorView::getPresenter() const {
    return _presenter;
}

size_t EditorView::getDocumentCount() const {
    return _documents.size();
}

const std::wstring &EditorView::getCurrentDocumentName() const {
    const auto index = _pageViewer->getCurrentIndex();
    if (index >= 0) {
        const rendell_ui::WidgetSharedPtr maybeDocument = _pageViewer->getPages()[index];
        const CodeEditorWidgetSharedPtr document =
            std::dynamic_pointer_cast<CodeEditorWidget>(maybeDocument);
        if (document) {
            for (auto it = _documents.begin(); it != _documents.end(); it++) {
                if (document == it->second) {
                    return it->first;
                }
            }
        }
    }

    static std::wstring empty;
    return empty;
}

const std::wstring &EditorView::getDocumentContent(const std::wstring &name) const {
    auto it = _documents.find(name);
    if (it == _documents.end()) {
        static const std::wstring emptyString;
        return emptyString;
    }
    return it->second->getText();
}

void EditorView::setPresenter(EditorPresenterSharedPtr presenter) {
    _presenter = presenter;
}

void EditorView::addDocument(const std::wstring &name, const std::wstring &text) {
    if (_documents.find(name) != _documents.end()) {
        return;
    }

    CodeEditorWidgetSharedPtr document = createTextEdit(_pageViewer, text);
    document->setAnchor(rendell_ui::Anchor::centerStretch);
    _documents.insert({name, document});

    _pageViewer->addPage(document);
    const auto model = _tabBar->getModel();
    model->addItem(name);
    _tabBar->setCurrentIndex(static_cast<int>(model->getSize()) - 1);
}

bool EditorView::removeDocument(const std::wstring &name) {
    auto it = _documents.find(name);
    if (it == _documents.end()) {
        return false;
    }

    const rendell_ui::StringListModelSharedPtr &tabModel = _tabBar->getModel();
    const auto &tabNames = tabModel->getData();
    auto tabNamesIt = std::find(tabNames.begin(), tabNames.end(), name);
    if (tabNamesIt == tabNames.end()) {
        return false;
    }
    const std::size_t tabIndex = std::distance(tabNames.begin(), tabNamesIt);

    tabModel->removeItem(tabIndex);
    _pageViewer->removePage(tabIndex);

    release_widget(it->second);
    _documents.erase(name);
    return true;
}

CodeEditorWidgetSharedPtr EditorView::createTextEdit(rendell_ui::WidgetWeakPtr parent,
                                                     const std::wstring &text) const {
    CodeEditorWidgetSharedPtr result = createCodeEditorWidget(parent);
    result->setAnchor(rendell_ui::Anchor::centerStretch);
    result->setText(text);
    return result;
}
