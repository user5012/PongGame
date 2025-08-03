#include <iostream>
#include "window.h"
#include "game.h"

const char K[] = "[*]";

int main(int argc, char* argv[])
{
    std::cout << K << " Rendering window...\n";
    window myWin({800, 600}, 60, sf::Style::Close);
    std::cout << K << " Success, have a nice time gaming!\n";
    myWin.mainLoop();
    return 0;
}

