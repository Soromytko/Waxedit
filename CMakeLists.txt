cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME Waxedit)
set(EXE_NAME waxedit)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILE_PATHS
    src/main.cpp
    src/App.cpp
    src/Window.cpp
    src/Viewport.cpp
    src/Widgets/Widget.cpp
    src/Widgets/Transform2D.cpp
    src/Widgets/Rectangle.cpp
    src/Widgets/Text.cpp
    src/Shaders/Shader.cpp
    src/Shaders/ShaderStorage.cpp
    src/Shaders/RectangleShader.cpp
    rendell-text/src/rendell_text.cpp
    rendell-text/src/FontRaster.cpp
    rendell-text/src/TextRenderer.cpp
    rendell-text/src/TextBuffer.cpp
    rendell-text/src/GlyphBuffer.cpp
    rendell-text/src/TextBatch.cpp
    rendell-text/src/RasteredFontStorage.cpp
    rendell-text/src/RasteredFontStorageManager.cpp
)

add_executable(${EXE_NAME} ${SOURCE_FILE_PATHS})

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
target_link_libraries(${EXE_NAME} glfw)

# FreeType
add_subdirectory(freetype)
target_link_libraries(${EXE_NAME} freetype)

# Rendell
add_subdirectory(rendell)
target_link_libraries(${EXE_NAME} rendell)

# Rendell-text
target_include_directories(${EXE_NAME} PRIVATE rendell-text/include)

# Glm
add_subdirectory(glm)
target_link_libraries(${EXE_NAME} glm)
