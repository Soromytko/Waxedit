cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME Waxedit)
set(EXE_NAME waxedit)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILE_PATHS
    src/main.cpp
    src/App.cpp
    src/MainRenderingContext.cpp
    src/RenderingWindow.cpp
)

set(HEADERS
    src/App.h
    src/MainRenderingContext.h
    src/IRenderingContext.h
    src/RenderingWindow.h
)

add_executable(${EXE_NAME} ${SOURCE_FILE_PATHS} ${HEADERS})

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
