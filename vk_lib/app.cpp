#include "app.hpp"
namespace ve{

void FirstApp::run(){
    while(lveWindow.shouldClose()){
        glfwPollEvents();
    }
}
}