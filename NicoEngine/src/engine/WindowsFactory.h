//
// Created by nicomane on 25/03/22.
//

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace WindowsFactory{
    class WindowsFactory {
    private:
        int width;
        int height;
        std::string name;
        GLFWwindow* window;
        VkInstance instance;
    public:
        WindowsFactory(){}
        WindowsFactory(int w,int h,std::string win_name)
        {
            width = w;
            height = h;
            name = win_name;
        }

        void run();
        void init();
        void initVulkan();
        void main();
        void close();
        void createInstance();
    };


}
