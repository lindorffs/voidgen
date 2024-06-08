# VoidGEN

A lightweight, LUA powered, 2D game engine.

## Usage
You can download the current unstable version of the engine from the releases page. Or build it from source.

VoidGEN loads the file `pre_init.lua` from the current working directory. If this file does not exist, or an update() and render() are not defined after this file executes, the engine will fail.

## Building From Source

Ultimately, VoidGEN is a single header file and a single .cpp file linked with SDL and LUA. This means it is possible to compile voidgen using a single command assuming the pre-requisite development libraries are installed and accessible by the compiler.

The SDL2 and LUA5.3 headers should be located in ``includes/LUA`` and ``includes/SDL2``.

```
g++ engine.cpp -I./includes -static-libstdc++ -static-libgcc \
-Wl,-Bstatic -lstdc++ -lpthread \
-Wl,-Bdynamic -lSDL2main -lSDL2 \
-lSDL2_image -lSDL2_mixer -lSDL2_ttf \
-llua5.3 -o VoidGEN.bin
```
