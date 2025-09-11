cmake_minimum_required(VERSION 3.21)
project(VulkanHello CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Vulkan REQUIRED)

# --- Fetch GLFW
include(FetchContent)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS   OFF CACHE BOOL "" FORCE)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4)
FetchContent_MakeAvailable(glfw)

# --- Engine library (adjust glob/patterns to your actual files)
file(GLOB ENGINE_SRC CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/vk_lib/*.cpp
)
add_library(VulkanEngine STATIC ${ENGINE_SRC})

# engine headers live here
target_include_directories(VulkanEngine
  PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/vk_lib
)

# make Vulkan & GLFW usage requirements (includes/defines) propagate
target_link_libraries(VulkanEngine
  PUBLIC Vulkan::Vulkan
         glfw
)

# avoid GLFW pulling OpenGL headers anywhere
target_compile_definitions(VulkanEngine PUBLIC GLFW_INCLUDE_NONE)

# --- Executable
add_executable(VK_project ${CMAKE_CURRENT_SOURCE_DIR}/code_index/main.cpp)

# Link exe to the engine (which already PUBLIC-links Vulkan+GLFW)
target_link_libraries(VK_project PRIVATE VulkanEngine)

# (Optional belt-and-suspenders: explicitly inherit GLFW's include dirs)
target_include_directories(VK_project PRIVATE
  $<TARGET_PROPERTY:glfw,INTERFACE_INCLUDE_DIRECTORIES>
)
target_include_directories(VulkanEngine
  PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/vk_lib
          ${CMAKE_CURRENT_SOURCE_DIR}/third_party   # contains the 'glm' folder
)
# If you had a GLSLC path, you can keep it:
# set(GLSLC_EXE "$ENV{VULKAN_SDK}/Bin/glslc.exe")