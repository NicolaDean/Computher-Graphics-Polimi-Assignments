#include "commonLibs.h"


namespace CommandBuffer{
    class CommandBuffer {
        VkCommandPool commandPool;
        VkCommandBuffer commandBuffer;
        VkDevice* device;
    public:
        CommandBuffer(){

        }
        CommandBuffer(VkDevice* dev){
            device = dev;
        }

        void init(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        void close();
        void createCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
        void createCommandBuffer();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

    };
}
