// Following the Vulkan Tutorial until the
// Drawing a triangle -> Setup -> Instance
// section (currently at https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance)
// create a 640 x 480 window, with title "Assignment 12", and list the global
// extensions supported by your O.S. 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#include "./myapp/MyApp.h"

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

int main() {
    //App::App app = App::App();
    MyApp::MyApp app = MyApp::MyApp();
    try {
        app.run(WIDTH,HEIGHT,"Assignment 12");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

    return 0;
}