cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME Waxedit)
set(EXE_NAME waxedit)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILE_PATHS
    src/main.cpp
    src/App.cpp
    src/Renderer.cpp
    src/Canvas.cpp
    src/HotkeyHandler.cpp
    src/Editor/Editor.cpp
    src/Editor/Commands/Invoker.cpp
    src/Editor/Commands/OpenFileCommand.cpp
    src/Editor/Commands/SaveDocumentsCommand.cpp
    src/Editor/Commands/CloseCurrentDocumentCommand.cpp

    # MVP
    src/Model/EditorModel.cpp
    src/Model/Document.cpp
    src/View/EditorView.cpp
    src/View/Widgets/CodeEditorWidget.cpp
    src/View/Widgets/LineNumberingWidget.cpp
    src/Presenter/EditorPresenter.cpp
)

set(HEADERS
    include/defines.h
    include/file_dialog.h

    #MVP
    include/Model/Document.h
    include/Model/EditorModel.h
    include/Model/EditorModelObserver.h
    include/View/IEditorView.h
    include/View/EditorView.h
    include/View/Widgets/CodeEditorWidget.h
    include/View/Widgets/LineNumberingWidget.h
    include/Presenter/EditorPresenter.h

    src/App.h
    src/IRenderer.h
    src/Renderer.h
    src/Canvas.h
    src/HotkeyHandler.h
    src/Editor/Editor.h
    src/Editor/Commands/Invoker.h
    src/Editor/Commands/Command.h
    src/Editor/Commands/NotStackableCommand.h
    src/Editor/Commands/OpenFileCommand.h
    src/Editor/Commands/SaveDocumentsCommand.h
    src/Editor/Commands/CloseCurrentDocumentCommand.h
)

set(WINDOWS_SOURCES
    src/Platform/windows_file_dialog.cpp
)

set(LINUX_SOURCES
    src/Platform/linux_file_dialog.cpp
)

include_directories(include)
add_executable(${EXE_NAME} ${SOURCE_FILE_PATHS} ${HEADERS})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_sources(${EXE_NAME} PRIVATE ${WINDOWS_SOURCES})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(${EXE_NAME} PRIVATE ${LINUX_SOURCES})
endif()

target_compile_definitions(${EXE_NAME}
    PRIVATE
        "FONT_ROOT_DIRECTORY=\"${CMAKE_SOURCE_DIR}/res/Fonts/\""
)

set(RENDELL_UI_FONT_ROOT_DIRECTORY ${CMAKE_SOURCE_DIR}/res/Fonts/)
add_subdirectory(rendell-stuff)
target_link_libraries(${EXE_NAME} PUBLIC rendell_stuff)
