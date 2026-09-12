#include <iostream>
#include "SDLApp.hpp"


int main() {
    SDLApp theApp;

    if (theApp.init() != 0) {
        return 1;
    }
    
    theApp.run();

    return 0;
}