#include "commonLibs.h"
#include "QueueFamily.h"

namespace DeviceManager{
    class DeviceManager {
    private:
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        uint32_t deviceCount = 0;
        VkInstance *instance;
        std::vector<VkPhysicalDevice> devices;

    public:
        /**
         * Constructor
         */
        DeviceManager(VkInstance * inst);
        DeviceManager(){}
        /**
         * Check presence of devices and select the first device compatible with
         * our application
         */
        void pickPhysicalDevice();

        /**
         * give each device a score and select the best one
         */
        void candidateSelection();

        /**
         * select a specific device chosen by user
         * @param deviceName name of device to select
         */
        void selectDeviceByName(char * deviceName);

        /**
         * get list of devices names
         */
        void getDeviceNames();

        /**
         * check if device is compatible with our app
         * @param device
         * @return
         */
        bool isDeviceSuitable(VkPhysicalDevice device);

        /**
         *
         * @return the selected device
         */
        VkPhysicalDevice getSelectedDevice();


        void printAllDeviceInfo(VkPhysicalDevice device);
    };
}

