# Vulkan-Rendering-Project
I want to learn Vulkan and will therefore try to use it to make some cool stuff.

EDIT: This project is starting to consume a lot of time lol, Vulkan was way harder than I thought and I already thought it was hard.

## Linux

Requirements:
- C++17 compiler
- CMake
- Vulkan loader and headers
- GLFW 3
- `glslc`
- Wayland development headers

NixOS:
```bash
nix develop
cmake -S . -B build
cmake --build build
./build/VK_project
```

Build:
```bash
cmake -S . -B build
cmake --build build
```

Run:
```bash
./build/VK_project
```
