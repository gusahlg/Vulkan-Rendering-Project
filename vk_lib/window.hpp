#pragma once
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
namespace ve{
    class LveWindow{
        public:
        LveWindow(int w, int h, std::string name);
        ~LveWindow();
        private:
        void initWindow();
        const int width;
        const int height;
        std::string windowName;
        GLFWwindow *window;
    };
}