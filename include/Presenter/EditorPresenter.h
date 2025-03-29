#pragma once
#include <memory>
#include <set>
#include <filesystem>
#include <View/IEditorView.h>
#include <Model/EditorModel.h>
#include <Model/Document.h>
#include <defines.h>

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
	bool saveAllDocuments();

	void onDocumentAdded(const std::wstring& name, const std::wstring& content) override;
	void onDocumentRemoved(const std::wstring& name) override;

	void updateDocuments();

private:
	IEditorViewWeakPtr _view;
	EditorModelSharedPtr _model{ nullptr };

};

DECLARE_SHARED_PTR_FACTORY(EditorPresenter)
