#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "WindowsFactory.h"

namespace App{
    class App {
    private:
        WindowsFactory::WindowsFactory windows;
    public:
        App();
        void run();
    };
}

