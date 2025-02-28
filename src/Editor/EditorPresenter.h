#pragma once
#include <memory>
#include <set>
#include <filesystem>
#include "IEditorView.h"
#include "EditorModel.h"
#include "Document.h"

class EditorPresenter final : public EditorModelObserver
{
public:
	EditorPresenter() = default;
	~EditorPresenter() = default;

	IEditorViewWeakPtr getView() const;
	EditorModelSharedPtr getModel() const;

	void setView(IEditorViewWeakPtr view);
	void setModel(EditorModelSharedPtr model);

	bool loadDocument(const std::filesystem::path& path);

	void onDocumentAdded(const std::wstring& name, const std::wstring& content) override;
	void onDocumentRemoved(const std::wstring& name) override;

private:
	IEditorViewWeakPtr _view;
	EditorModelSharedPtr _model{ nullptr };

};

typedef std::shared_ptr<EditorPresenter> EditorPresenterSharedPtr;

template <typename... Args>
EditorPresenterSharedPtr makeEditorPresenter(Args&&... args)
{
	return std::make_shared<EditorPresenter>(std::forward<Args>(args)...);
}
