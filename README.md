# What is Waxedit?
This is a lightweight, fast and simple text editor. It contains the necessary functionality for comfortable text editing or writing simple scripts. Waxedit is considered to be cross-platform (at least Linux and Windows). However, at the moment, reliable support is provided only for Windows. 

# Demo
![demo](assets/Waxedit-demo.gif)

# Features
- Opening, editing and saving file.
- Basic editing functionality: typing text, erasing text, line breaks.
- Loading (hardcoded file name) and rasterization font using [freetype](https://github.com/freetype/freetype).
- Lightweight due to its own rendering library ([rendell](https://github.com/Soromytko/rendell)) and GUI ([rendell-ui](https://github.com/Soromytko/rendell-ui)).
- Optimizing glyph rendering using caching. 

# Planned Features
- Standard set of hotkeys (Ctrl+A, Ctrl+X, etc.).
- Syntax highlighting.
- Auto-completion (based on open documents).
- Search in documents.
- Working with multiple files.

# Build
Clone this repository with the `--recursive` option
```
git clone --recursive https://github.com/Soromytko/Waxedit.git
```
CMake 13.3 is required to build the project.

```
cd build
cmake ..
cmake --build .
```