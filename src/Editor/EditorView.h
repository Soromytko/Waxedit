#pragma once
#include <memory>
#include <unordered_map>
#include <rendell_ui/rendell_ui.h>
#include "IEditorView.h"
#include "../Canvas.h"
#include "EditorPresenter.h"
#include "EditorModel.h"
#include "../defines.h"

class EditorView final : public IEditorView
{
public:
	EditorView(EditorCanvasSharedPtr canvas);
	~EditorView() = default;

	EditorCanvasSharedPtr getCanvas() const;
	EditorPresenterSharedPtr getPresenter() const;
	const std::wstring& getDocumentContent(const std::wstring& name) const override;

	void setPresenter(EditorPresenterSharedPtr presenter);

	void addDocument(const std::wstring& name, const std::wstring& text) override;
	void removeDocument(const std::wstring& name) override;

private:
	rendell_ui::TextEditWidgetSharedPtr createTextEdit(rendell_ui::WidgetWeakPtr parent, const std::wstring& text) const;

	EditorPresenterSharedPtr _presenter;
	EditorCanvasSharedPtr _canvas;
	rendell_ui::RectangleWidgetSharedPtr _rootWidget;

	std::unordered_map<std::wstring, rendell_ui::TextEditWidgetSharedPtr> _documents;
};

DECLARE_SHARED_PTR_FACTORY(EditorView)
