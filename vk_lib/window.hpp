#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <vulkan/vulkan.h>
namespace ve {
class LveWindow {
public:
  LveWindow(int w, int h, std::string name);
  ~LveWindow();
  LveWindow(const LveWindow &) = delete;
  LveWindow &operator=(const LveWindow &) = delete;
  bool shouldClose() { return glfwWindowShouldClose(window); }
  VkExtent2D getExtent() {
    return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
  }
  bool wasWindowResized() { return frameBufferResized; }
  void resetWindowResizedFlag() { frameBufferResized = false; }
  GLFWwindow *getGLFWwindow() const { return window; }
  void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

private:
  static void frameBufferResizedCallback(GLFWwindow *window, int width,
                                         int height);
  void initWindow();
  int width;
  int height;
  bool frameBufferResized = false;
  std::string windowName;
  GLFWwindow *window;
};
} // namespace ve
