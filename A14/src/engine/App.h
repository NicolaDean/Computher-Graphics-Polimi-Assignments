#include "commonLibs.h"
#include "DeviceManager.h"
#include "LogicDeviceManager.h"
#include "WindowsSurface.h"
#include "CommandBuffer.h"
#include "SwapChain.h"
namespace App{
    class App {
    private:
        int width;
        int height;
        std::string name;
        GLFWwindow* window;
        VkInstance instance;
        DeviceManager::DeviceManager devicesManager;
        DeviceManager::LogicDeviceManager logicDeviceManager;
        Presentation::WindowsSurface windowsSurface;
        CommandBuffer::CommandBuffer commandBuffer;
        Presentation::SwapChain swapChain;

    public:
        App(){}

        App(int w,int h,std::string win_name)
        {
            width = w;
            height = h;
            name = win_name;
        }
    private:
        void init();
        void initVulkan();
        void main();
        void appLoop();
        void close();
        void createInstance();
        void printExtensionNames();
        GLFWwindow* getWindow();
    public:
        void run();
        void loop();
    };


}