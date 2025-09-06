cmake_minimum_required(VERSION 3.21)
project(VK_project CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Vulkan REQUIRED)

# use glslc from the SDK
set(GLSLC_EXE "$ENV{VULKAN_SDK}/Bin/glslc.exe")

# fetch GLFW (header ends up in build/_deps/glfw-src/include)
include(FetchContent)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4)

# Linking Vulkan engine library
file(GLOB ENGINE_SRC CONFIGURE_DEPENDS vk_lib/*.cpp)
add_library(VulkanEngine STATIC ${ENGINE_SRC})
target_include_directories(VulkanEngine PUBLIC code_index/engine)

add_executable(VK_project code_index/main.cpp)   # was src/main.cpp
target_link_libraries(VK_project PRIVATE Vulkan::Vulkan glfw)
target_compile_definitions(VK_project PRIVATE GLFW_INCLUDE_NONE)
# (plus the shader rules from my previous message)
