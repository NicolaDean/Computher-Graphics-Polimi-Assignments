#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "../engine/App.h"

namespace MyApp{
    class MyApp: public App::App{

    public:
        MyApp(int width,int h,std::string win_name):App::App(width,h,win_name){
            //Some Code....
        }

        void loop(){
            std::cout<<"Banana\n";
        }
    };
}

