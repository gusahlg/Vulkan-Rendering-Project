#pragma once
#include "window.hpp"
#include "ve_pipeline.hpp"
#include "lve_device.hpp"
#include "lve_swap_chain.hpp"
#include "ve_model.hpp"
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
        void loadModels();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();
        void recreateSwapChain();
        void recordCommandBuffer(int imageIndex);

        LveWindow lveWindow{WIDTH, HEIGHT, "VK Rendering Project"};
        LveDevice lveDevice{lveWindow};
        std::unique_ptr<LveSwapChain> lveSwapChain;
        std::unique_ptr<LvePipeline> lvePipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        std::unique_ptr<LveModel> lveModel;
    };
}