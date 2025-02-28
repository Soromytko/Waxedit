#pragma once
#include <memory>
#include <unordered_map>
#include <rendell_ui/rendell_ui.h>
#include "IEditorView.h"
#include "../Canvas.h"
#include "EditorPresenter.h"
#include "EditorModel.h"

class EditorView final : public IEditorView
{
public:
	EditorView(CanvasSharedPtr canvas);
	~EditorView() = default;

	CanvasSharedPtr getCanvas() const;
	EditorPresenterSharedPtr getPresenter() const;

	void setPresenter(EditorPresenterSharedPtr presenter);

	void addDocument(const std::wstring& name, const std::wstring& text) override;
	void removeDocument(const std::wstring& name) override;

private:
	rendell_ui::TextEditWidget* createTextEdit(rendell_ui::Widget* parent, const std::wstring& text) const;

	EditorPresenterSharedPtr _presenter;
	CanvasSharedPtr _canvas;
	rendell_ui::RectangleSharedPtr _rootWidget;

	std::unordered_map<std::wstring, rendell_ui::TextEditWidget*> _documents;
};

typedef std::shared_ptr<EditorView> EditorViewSharedPtr;

template <typename... Args>
EditorViewSharedPtr makeEditorView(Args&&... args)
{
	return std::make_shared<EditorView>(std::forward<Args>(args)...);
}
