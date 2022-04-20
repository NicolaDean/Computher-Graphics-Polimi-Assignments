#include "DeviceManager.h"

namespace DeviceManager{
    DeviceManager::DeviceManager(VkInstance * inst){
        instance = inst;
    }

    void DeviceManager::pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(*instance, &deviceCount, nullptr);

        if (deviceCount == 0) {
           // throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        //devices.resize(deviceCount);
        vkEnumeratePhysicalDevices(*instance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (isDeviceSuitable(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            //throw std::runtime_error("failed to find a suitable GPU!");
        }

    }

    void DeviceManager::candidateSelection(){
        //TODO candidate Selection

        // eg give a score to each devie
    }

    void DeviceManager::getDeviceNames() { //TODO print a list of all devices
         }

    void DeviceManager::selectDeviceByName(char *deviceName) { //TODO select a specific device
         }

    bool DeviceManager::isDeviceSuitable(VkPhysicalDevice device) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader;
    }
}