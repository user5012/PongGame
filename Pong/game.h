#include"Audio.h"
#include<SFML/Graphics.hpp>

class game  
{  
public:  
   game(sf::Vector2f ballVelocity = {0,0});  
   game(const game&) = delete; // Delete copy constructor  
   game& operator=(const game&) = delete; // Delete copy assignment operator  
   game(game&&) = default; // Allow move constructor  
   game& operator=(game&&) = default; // Allow move assignment operator  
   void drawStart(sf::RenderWindow &window);  
   auto getState() { return this->state; }  
   void handleGameStates(sf::RenderWindow& window);  

private:  
   Audio audio;  
   enum GameState {  
       Start,  
       WinPlayer1,  
       WinPlayer2,  
       PlayingEasy,  
       PlayingHard  
   };  
   sf::RectangleShape createRect(sf::Vector2f size, sf::Vector2f position, sf::Color color);  
   std::unique_ptr<sf::Text> createText(sf::String txt, unsigned int fontSize, sf::Color color, sf::Vector2f position) const;
   sf::RectangleShape pad1;  
   sf::RectangleShape pad2;  
   sf::RectangleShape ball;  
   sf::Vector2f ballVelocity;  
   int pointsP1 = 0;  
   int pointsP2 = 0;  
   std::unique_ptr<sf::Text> WelcomeText, PlayHardText, PlayEasyText, TextPointsP1 ,TextPointsP2, winnerText, WordWinnerText, RestartText;
   sf::Font font;  
   GameState state;  
   void gameLogic(float ballVelocity);  
   void resetBall() {  
       ball.setPosition({ 400, 300 });  
   }  
   auto turnToNegative(auto Number) {  
       return -Number;  
   }  
   void GameDrawer(sf::RenderWindow& wnd);
   void wonGame(bool isPlayer1, sf::RenderWindow& wnd);
};
