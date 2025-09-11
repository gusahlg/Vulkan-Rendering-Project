#pragma once
#include "lve_device.hpp"
#include <vector>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
namespace ve{

class LveModel{
    public:
        struct Vertex{
            glm::vec2 positions;
            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };
        LveModel(LveDevice &device, const std::vector<Vertex> &vertices);
        ~LveModel();
        LveModel(const LveWindow&) = delete;
        LveModel &operator=(const LveWindow&) = delete;
        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);
    private: 
        void createVertexBuffers(const std::vector<Vertex> &vertices);
        LveDevice& lveDevice;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;
};
}