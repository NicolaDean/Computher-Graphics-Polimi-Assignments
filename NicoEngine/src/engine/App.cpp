//
// Created by nicomane on 25/03/22.
//

#include "App.h"
namespace App{
    App::App(){

    }
    void App::run() {
        windows = WindowsFactory::WindowsFactory(400,400,"Test");
        windows.run();
    }
}

