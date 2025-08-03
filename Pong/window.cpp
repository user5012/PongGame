#include "window.h"  

window::window(sf::Vector2u winSize, unsigned int framerateCap, std::uint32_t Style)  
: myGame(sf::Vector2f(5.0f, 3.0f)) // Use direct initialization in the initializer list  
{  
   this->windowSize = winSize;  
   this->frameRateCap = framerateCap;  
   this->Style = Style;  
   this->myWIn = sf::RenderWindow(sf::VideoMode(this->windowSize), "Lia vs Kyrma", this->Style);  
   this->myWIn.setFramerateLimit(frameRateCap);  
}  

void window::mainLoop()  
{  
   while (this->myWIn.isOpen()) {  
       while (const std::optional event = this->myWIn.pollEvent()) {  
           if (event->is<sf::Event::Closed>()) {  
               this->myWIn.close();  
           }  
       }  
       this->myWIn.clear(sf::Color(153, 255, 153)); //make window green  
       //mainloop  
       this->myGame.handleGameStates(this->myWIn);  

       this->myWIn.display(); //end the current frame  
   }  
}
