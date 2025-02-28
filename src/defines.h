#pragma once

#define DECLARE_SHARED_PTR_FACTORY(ClassName) \
	template <typename... Args> \
    std::shared_ptr<ClassName> make ## ClassName(int arg) { \
		return std::make_shared<ClassName>(std::forward<Args>(args)...); \
    }

//DECLARE_SHARED_PTR_FACTORY(EditorModel)
