#include "window.hpp"
#if defined(__linux__)
#define GLFW_EXPOSE_NATIVE_WAYLAND
#include <GLFW/glfw3native.h>
#endif
#include <cstdlib>
#include <stdexcept>
namespace ve{

LveWindow::LveWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name}{
    initWindow();
}
LveWindow::~LveWindow(){
    glfwDestroyWindow(window);
    glfwTerminate();
}
void LveWindow::initWindow(){
#if defined(__linux__)
    glfwInitHint(
        GLFW_PLATFORM,
        std::getenv("WAYLAND_DISPLAY") != nullptr ? GLFW_PLATFORM_WAYLAND : GLFW_PLATFORM_X11);
#endif
    if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error("failed to initialize GLFW");
    }
    if (glfwVulkanSupported() != GLFW_TRUE) {
        throw std::runtime_error("GLFW reports that Vulkan is not supported");
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("failed to create GLFW window");
    }
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, frameBufferResizedCallback);
}
void LveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface){
#if defined(__linux__)
    if (glfwGetPlatform() == GLFW_PLATFORM_WAYLAND) {
        auto createWaylandSurface =
            reinterpret_cast<PFN_vkCreateWaylandSurfaceKHR>(
                vkGetInstanceProcAddr(instance, "vkCreateWaylandSurfaceKHR"));
        if (createWaylandSurface == nullptr) {
            throw std::runtime_error("vkCreateWaylandSurfaceKHR is unavailable");
        }

        VkWaylandSurfaceCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
        createInfo.display = glfwGetWaylandDisplay();
        createInfo.surface = glfwGetWaylandWindow(window);

        if (createInfo.display == nullptr || createInfo.surface == nullptr) {
            throw std::runtime_error("failed to query native Wayland window handles");
        }

        VkResult result = createWaylandSurface(instance, &createInfo, nullptr, surface);
        if (result != VK_SUCCESS) {
            throw std::runtime_error(
                "failed to create Wayland window surface (VkResult=" + std::to_string(result) +
                ")");
        }
        return;
    }
#endif

    VkResult result = glfwCreateWindowSurface(instance, window, nullptr, surface);
    if(result != VK_SUCCESS){
        const char *description = nullptr;
        int glfwError = glfwGetError(&description);
        throw std::runtime_error(
            "failed to create window surface (VkResult=" + std::to_string(result) +
            ", GLFW error=" + std::to_string(glfwError) +
            (description ? ", " + std::string(description) : "") + ")");
    }
}

void LveWindow::frameBufferResizedCallback(GLFWwindow *window, int width, int height){
    auto lveWindow = reinterpret_cast<LveWindow*>(glfwGetWindowUserPointer(window));
    lveWindow->frameBufferResized = true;
    lveWindow->width = width;
    lveWindow->height = height;
}
}
