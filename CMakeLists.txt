cmake_minimum_required(VERSION 3.21)
project(VulkanHello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Vulkan REQUIRED)

if(UNIX AND NOT APPLE)
  find_path(WAYLAND_CLIENT_INCLUDE_DIR wayland-client.h)
  if(NOT WAYLAND_CLIENT_INCLUDE_DIR)
    message(FATAL_ERROR "wayland-client.h not found")
  endif()
endif()

# --- GLFW
find_package(glfw3 QUIET)
if (NOT TARGET glfw)
  include(FetchContent)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
  )
  FetchContent_MakeAvailable(glfw)
endif()

# --- Shaders
find_program(GLSLC_EXECUTABLE glslc REQUIRED)
set(SHADER_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${SHADER_OUTPUT_DIR})

add_custom_command(
  OUTPUT ${SHADER_OUTPUT_DIR}/simple_shader.vert.spv
  COMMAND ${GLSLC_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/shaders/simple_shader.vert -o ${SHADER_OUTPUT_DIR}/simple_shader.vert.spv
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/shaders/simple_shader.vert
  VERBATIM
)

add_custom_command(
  OUTPUT ${SHADER_OUTPUT_DIR}/simple_shader.frag.spv
  COMMAND ${GLSLC_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/shaders/simple_shader.frag -o ${SHADER_OUTPUT_DIR}/simple_shader.frag.spv
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/shaders/simple_shader.frag
  VERBATIM
)

add_custom_target(Shaders ALL
  DEPENDS
    ${SHADER_OUTPUT_DIR}/simple_shader.vert.spv
    ${SHADER_OUTPUT_DIR}/simple_shader.frag.spv
)

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
  PRIVATE
    ${WAYLAND_CLIENT_INCLUDE_DIR}
)

# Propagate dependencies to dependents of VulkanEngine
target_link_libraries(VulkanEngine
  PUBLIC Vulkan::Vulkan
         glfw
)

target_compile_definitions(VulkanEngine PUBLIC VE_SHADER_DIR="${SHADER_OUTPUT_DIR}")
add_dependencies(VulkanEngine Shaders)

# --- Executable --------------------------------------------------------------
add_executable(VK_project ${CMAKE_CURRENT_SOURCE_DIR}/code_index/main.cpp)
target_link_libraries(VK_project PRIVATE VulkanEngine)
