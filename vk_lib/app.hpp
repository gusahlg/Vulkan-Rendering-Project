#pragma once
#include "window.hpp"
#include "ve_pipeline.hpp"
#include "my_engine_device.hpp"
namespace ve{
    class FirstApp{
    public:
        static constexpr int WIDTH = 1280;
        static constexpr int HEIGHT = 720;
        void run();
    private:
        LveWindow lveWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
        LveDevice lveDevice{lveWindow};
        LvePipeline lvePipeline{lveDevice, 
            "shaders/simple_shader.vert.spv",
            "shaders/simple_shader.frag.spv", 
            LvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
    };
}