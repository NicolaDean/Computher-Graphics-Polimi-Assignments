#include "commonLibs.h"

namespace DeviceManager{

    class LogicDeviceManager {

    private:
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;

    public:
        LogicDeviceManager(){}

        void generateLogicDevice(VkPhysicalDevice physicalDevice,VkSurfaceKHR surface);
        VkDevice* getDevice();
        void clean();
    };

}
