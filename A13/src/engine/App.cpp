#include "App.h"
namespace App{

    App::App(){

    }

    void App::run(int w,int h,std::string title) {
        windows = WindowsFactory::WindowsFactory(w,h,title);
        windows.run();
    }
}