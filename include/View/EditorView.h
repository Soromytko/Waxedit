#pragma once
#include <memory>
#include <unordered_map>
#include <rendell_ui/rendell_ui.h>
#include <defines.h>
#include <Presenter/EditorPresenter.h>
#include <Model/EditorModel.h>
#include "IEditorView.h"
#include "Widgets/CodeEditorWidget.h"
#include "../src/Canvas.h"

class EditorView final : public IEditorView
{
public:
	EditorView(EditorCanvasSharedPtr canvas);
	~EditorView() = default;

	EditorCanvasSharedPtr getCanvas() const;
	EditorPresenterSharedPtr getPresenter() const;
	size_t getDocumentCount() const override;
	const std::wstring& getCurrentDocumentName() const override;
	const std::wstring& getDocumentContent(const std::wstring& name) const override;

	void setPresenter(EditorPresenterSharedPtr presenter);

	void addDocument(const std::wstring& name, const std::wstring& text) override;
	bool removeDocument(const std::wstring& name) override;

private:
	CodeEditorWidgetSharedPtr createTextEdit(rendell_ui::WidgetWeakPtr parent, const std::wstring& text) const;

	EditorPresenterSharedPtr _presenter;
	EditorCanvasSharedPtr _canvas;
	rendell_ui::RectangleWidgetSharedPtr _rootWidget;
	rendell_ui::TabBarWidgetSharedPtr _tabBar;
	rendell_ui::PageViewerWidgetSharedPtr _pageViewer;

	std::unordered_map<std::wstring, CodeEditorWidgetSharedPtr> _documents;
};

DECLARE_SHARED_PTR_FACTORY(EditorView)
