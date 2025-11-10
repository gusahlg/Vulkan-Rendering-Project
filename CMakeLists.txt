cmake_minimum_required(VERSION 3.21)
project(VulkanHello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Vulkan REQUIRED)

# --- GLFW via FetchContent
include(FetchContent)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
FetchContent_Declare(glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# --- Engine library ----------------------------------------------------------
# Recurse to pick up vk_lib/engine_core/*.cpp (and other subdirs like rendering)
file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/vk_lib/*.cpp
)

add_library(VulkanEngine STATIC ${ENGINE_SRC})

# Public headers live in vk_lib and its subfolders; glm is under third_party/glm
target_include_directories(VulkanEngine
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/vk_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/vk_lib/engine_core
    ${CMAKE_CURRENT_SOURCE_DIR}/vk_lib/rendering
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party         # contains the 'glm' dir
)

# Propagate dependencies to dependents of VulkanEngine
target_link_libraries(VulkanEngine
  PUBLIC Vulkan::Vulkan
         glfw
)

# Prevent GLFW from dragging in OpenGL headers
target_compile_definitions(VulkanEngine PUBLIC GLFW_INCLUDE_NONE)

# --- Executable --------------------------------------------------------------
add_executable(VK_project ${CMAKE_CURRENT_SOURCE_DIR}/code_index/main.cpp)
target_link_libraries(VK_project PRIVATE VulkanEngine)
