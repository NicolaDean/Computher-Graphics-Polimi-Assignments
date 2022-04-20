#include "WindowsFactory.h"
#include <iostream>
#include <vector>
namespace WindowsFactory{
    void WindowsFactory::run(){
        init();
        initVulkan();
        main();
        close();
    }

    GLFWwindow* WindowsFactory::getWindow(){
        return window;
    }

    void WindowsFactory::init(){
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    }

    void WindowsFactory::initVulkan(){
        WindowsFactory::createInstance();
        WindowsFactory::printExtensionNames();
    }

    void WindowsFactory::main(){
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void WindowsFactory::close(){
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    /**
     * It allow to specify some useful information needed by driver in order to optimize the application
     */
    void WindowsFactory::createInstance() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        //This next struct is not optional and tells the Vulkan driver which global extensions and validation layers
        // we want to use.
        // Global here means that they apply to the entire program and not a specific device,which will become clear in the next few chapters.


        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            //throw std::runtime_error("failed to create instance!");
            printf("failed to create instance!\n");
        }

    }

    /**
     * Print names of all available extensions
     */
    void WindowsFactory::printExtensionNames(){
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "available extensions:\n";

        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }

}