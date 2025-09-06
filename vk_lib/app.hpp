#pragma once
#include "window.hpp"
namespace ve{
    class FirstApp{
        public:
        static constexpr int WIDTH = 1280;
        static constexpr int HEIGHT = 720;
        void run(){

        }
        private:
        LveWindow lveWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
    };
}