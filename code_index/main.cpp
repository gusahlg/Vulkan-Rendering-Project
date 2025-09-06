#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../vk_lib/app.hpp"
#include <vector>
#include <cstdlib>
#include <stdexcept>
int main(){
    ve::FirstApp app{};
    try{
        app.run();
    }
    catch(const std::exception &e){
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
    return 0;
}
