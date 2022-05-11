#include "App.h"

namespace App{
    void App::run(){
        init();
        initVulkan();
        main();
        close();
    }

    GLFWwindow* App::getWindow(){
        return window;
    }

    void App::init(){

        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
        devicesManager = DeviceManager::DeviceManager(&instance);
        swapChain = Presentation::SwapChain();
    }

    void App::initVulkan(){
        //CREATE INSTANCE
        createInstance();
        printExtensionNames();
        //Create Presentation Layer
        windowsSurface.createSurface(instance,window);
        //QUERY FOR AVAILABLE DEVICES AND SELECT THE BEST ONE
        devicesManager.pickPhysicalDevice(windowsSurface.getSurface());
        //GENERATE A LOGIC DEVICE INTERFACE OF THE SELECTED DEVICE
        logicDeviceManager.generateLogicDevice(devicesManager.getSelectedDevice(),windowsSurface.getSurface());

        commandBuffer = CommandBuffer::CommandBuffer(logicDeviceManager.getDevice());
        swapChain.createSwapChain(devicesManager.getSelectedDevice(),*logicDeviceManager.getDevice(),windowsSurface.getSurface(),window);
        swapChain.createImageView(*logicDeviceManager.getDevice());
        //createRenderPass(); -> A0???
        //createGraphicsPipeline(); ->A0???
        //createFramebuffers(); -> A0???

        commandBuffer.init(devicesManager.getSelectedDevice(),windowsSurface.getSurface());


    }

    void App::loop() {
        //USER MUST OVERRIDE THIS FUNCTION
        std::cout<<"Original\n";
    }

    void App::appLoop() {
        std::cout<<"User loop";

        while(!glfwWindowShouldClose(window)){
            loop();
        }
    }

    void App::main(){
        //TODO launch "appLoop()" in a separated thread

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            //loop();
        }
    }

    void App::close(){
        swapChain.close(*logicDeviceManager.getDevice());
        commandBuffer.close();
        vkDestroyInstance(instance, nullptr);
        windowsSurface.clean(instance);
        logicDeviceManager.clean();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    /**
     * It allow to specify some useful information needed by driver in order to optimize the application
     */
    void App::createInstance() {
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
            throw std::runtime_error("failed to create instance!");
        }

    }

    /**
     * Print names of all available extensions
     */
    void App::printExtensionNames(){
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