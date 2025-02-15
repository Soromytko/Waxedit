cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME Waxedit)
set(EXE_NAME waxedit)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILE_PATHS
    src/main.cpp
    src/App.cpp
    src/Renderer.cpp
    src/Canvas.cpp
)

set(HEADERS
    src/App.h
    src/IRenderer.h
    src/Renderer.h
    src/Canvas.h

    src/file_dialog.h
)

set(WINDOWS_SOURCES
    src/Platform/windows_file_dialog.cpp
)

set(LINUX_SOURCES
    src/Platform/linux_file_dialog.cpp
)

add_executable(${EXE_NAME} ${SOURCE_FILE_PATHS} ${HEADERS})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_sources(${EXE_NAME} PRIVATE ${WINDOWS_SOURCES})
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(${EXE_NAME} PRIVATE ${LINUX_SOURCES})
endif()

# Rendell
add_subdirectory(rendell)
target_link_libraries(${EXE_NAME} rendell)

# Glm
add_subdirectory(glm)
target_link_libraries(${EXE_NAME} glm)

# Rendell-ui
set(GLM_LIB glm)
set(RENDELL_LIB rendell)
add_subdirectory(rendell-ui)
target_link_libraries(${EXE_NAME} rendell_ui)
