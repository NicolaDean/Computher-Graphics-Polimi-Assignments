#include "commonLibs.h"



namespace Presentation{
    class WindowsSurface {
    private:
        VkSurfaceKHR surface;
    public:
        WindowsSurface();
        void createSurface(VkInstance instance,GLFWwindow* window);
        void clean(VkInstance instance);
        VkSurfaceKHR getSurface();
    };
}


