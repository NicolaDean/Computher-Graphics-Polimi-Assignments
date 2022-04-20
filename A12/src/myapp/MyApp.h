#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "../engine/App.h"

namespace MyApp{
    class MyApp: public App::App{

        int playerPos;
        int playerPoints;
    public:
        MyApp(){
            //Some Code....
        }

    };
}

