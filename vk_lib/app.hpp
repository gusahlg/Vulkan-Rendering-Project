#pragma once
#include "window.hpp"
#include "lve_device.hpp"
#include "lve_game_object.hpp"
#include "ve_renderer.hpp"

// std
#include <memory>
#include <vector>
namespace ve{
    class FirstApp{
    public:
        static constexpr int WIDTH = 1280;
        static constexpr int HEIGHT = 720;
        FirstApp();
        ~FirstApp();
        FirstApp(const FirstApp&) = delete;
        FirstApp& operator=(const FirstApp&) = delete;
        void run();
    private:
        void loadGameObjects();

        LveWindow lveWindow{WIDTH, HEIGHT, "VK Rendering Project"};
        LveDevice lveDevice{lveWindow};
        LveRenderer lveRenderer{lveWindow, lveDevice};
        std::vector<LveGameObject> gameObjects;
    };
}