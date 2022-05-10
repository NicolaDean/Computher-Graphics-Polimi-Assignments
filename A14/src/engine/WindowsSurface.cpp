

#include "WindowsSurface.h"

namespace Presentation{
    Presentation::WindowsSurface::WindowsSurface(){

    }

    void Presentation::WindowsSurface::createSurface(VkInstance instance,GLFWwindow* window){
        if (glfwCreateWindowSurface(instance,window, nullptr,&surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void Presentation::WindowsSurface::clean(VkInstance instance) {
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
    }

    VkSurfaceKHR Presentation::WindowsSurface::getSurface() {
        return surface;
    }
}
