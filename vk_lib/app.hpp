#pragma once
#include "window.hpp"
#include "ve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"
#include <memory>
#include <vector>
namespace ve{
    class FirstApp{
    public:
        static constexpr int WIDTH = 1280;
        static constexpr int HEIGHT = 720;
        FirstApp();
        ~FirstApp();
        FirstApp(const LveWindow&) = delete;
        FirstApp &operator=(const LveWindow&) = delete;
        void run();
    private:
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();
        LveWindow lveWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
        LveDevice lveDevice{lveWindow};
        LveSwapChain lveSwapChain{lveDevice, lveWindow.getExtent()};
        std::unique_ptr<LvePipeline> lvePipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
    };
}