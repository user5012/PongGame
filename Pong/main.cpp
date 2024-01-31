#include <iostream>
#include <SFML/Graphics.hpp>

enum GameState {
    Start,
    WinPlayer1,
    WinPlayer2,
    PlayingEasy,
    PlayingHard
};

const char* K = "[+]";


void drawPad1(sf::RenderWindow& window, sf::RectangleShape& pad1) {
    window.draw(pad1);
}

void drawPad2(sf::RenderWindow& window, sf::RectangleShape& pad2) {
    window.draw(pad2);
}

void drawBall(sf::RenderWindow& window, sf::RectangleShape& ball) {
    window.draw(ball);
}

void drawText(sf::RenderWindow& window, const std::string& text, float x, float y, int fontSize) {
    sf::Font font;
    if (!font.loadFromFile("SweetieBubbleGum-Regular.ttf")) {
        std::cerr << K << " error while loading font: " << sf::err << std::endl;
    }

    sf::Text gameOver;
    gameOver.setFont(font);
    gameOver.setString(text);
    gameOver.setCharacterSize(fontSize);
    gameOver.setFillColor(sf::Color::Black);
    gameOver.setPosition(x, y);

    window.draw(gameOver);
}

void ballReset(sf::RectangleShape& ball) {
    ball.setPosition(sf::Vector2f(400.f, 300.f));
}

void handleGameLogicEasy(sf::RectangleShape& pad1, sf::RectangleShape& pad2, sf::RectangleShape& ball, sf::RenderWindow& window, sf::Vector2f& ballVelocity, GameState& gameState, int& pointsP1, int& pointsP2) {
    float pad1y = pad1.getPosition().y;  // Get the current y position of pad1

    float pad2y = pad2.getPosition().y;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (pad1y != 0) {
            pad1y -= 5.0f;
            pad1.setPosition(sf::Vector2f(pad1.getPosition().x, pad1y));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (pad1y != 500) {
            pad1y += 5.0f;
            pad1.setPosition(sf::Vector2f(pad1.getPosition().x, pad1y));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (pad2y != 0) {
            pad2y -= 5.0f;
            pad2.setPosition(sf::Vector2f(pad2.getPosition().x, pad2y));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (pad2y != 500.f) {
            pad2y += 5.0f;
            pad2.setPosition(sf::Vector2f(pad2.getPosition().x, pad2y));
        }
    }


    ball.move(ballVelocity);

    //point counter
    if (ball.getPosition().x <= 0) {
        pointsP1++;
        std::cout << K << pointsP1 << std::endl;
        ballReset(ball);
    }
    if (ball.getPosition().x >= window.getSize().x - ball.getSize().x) {
        pointsP2++;
        std::cout << K << pointsP2 << std::endl;
        ballReset(ball);
    }

    // Collision with window borders
    if (ball.getPosition().y <= 0 || ball.getPosition().y >= window.getSize().y - ball.getSize().y) {
        ballVelocity.y = -ballVelocity.y;
    }

    //collision with pads
    if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds()) || ball.getGlobalBounds().intersects(pad2.getGlobalBounds())) {
        ballVelocity.x = -ballVelocity.x;
    }

    //declair winner
    if (pointsP1 == 10) {
        gameState = WinPlayer2;
    }

    if (pointsP2 == 10) {
        gameState = WinPlayer1;
    }

    //std::cout << K << " ball position " << ball.getPosition().x << " " << ball.getPosition().y << std::endl;

}

void handleGameLogicHard(sf::RectangleShape& pad1, sf::RectangleShape& pad2, sf::RectangleShape& ball, sf::RenderWindow& window, sf::Vector2f& ballVelocity, GameState& gameState, int& pointsP1, int& pointsP2) {
    float pad1y = pad1.getPosition().y;  // Get the current y position of pad1

    float pad2y = pad2.getPosition().y;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (pad1y != 0) {
            pad1y -= 2.0f;
            pad1.setPosition(sf::Vector2f(pad1.getPosition().x, pad1y));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (pad1y != 500) {
            pad1y += 2.0f;
            pad1.setPosition(sf::Vector2f(pad1.getPosition().x, pad1y));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (pad2y != 0) {
            pad2y -= 2.0f;
            pad2.setPosition(sf::Vector2f(pad2.getPosition().x, pad2y));
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (pad2y != 500.f) {
            pad2y += 2.0f;
            pad2.setPosition(sf::Vector2f(pad2.getPosition().x, pad2y));
        }
    }


    ball.move(ballVelocity);

    //point counter
    if (ball.getPosition().x <= 0) {
        pointsP1++;
        std::cout << K << pointsP1 << std::endl;
        ballReset(ball);
    }
    if (ball.getPosition().x >= window.getSize().x - ball.getSize().x) {
        pointsP2++;
        std::cout << K << pointsP2 << std::endl;
        ballReset(ball);
    }

    // Collision with window borders
    if (ball.getPosition().y <= 0 || ball.getPosition().y >= window.getSize().y - ball.getSize().y) {
        ballVelocity.y = -ballVelocity.y;
    }

    //collision with pads
    if (ball.getGlobalBounds().intersects(pad1.getGlobalBounds()) || ball.getGlobalBounds().intersects(pad2.getGlobalBounds())) {
        ballVelocity.x = -ballVelocity.x;
    }

    //declair winner
    if (pointsP1 == 10) {
        gameState = WinPlayer2;
    }

    if (pointsP2 == 10) {
        gameState = WinPlayer1;
    }

    //std::cout << K << " ball position " << ball.getPosition().x << " " << ball.getPosition().y << std::endl;

}


int main(int argc, char* argv[])
{
    std::cout << K << " Rendering window...\n";
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window", sf::Style::Close); //render window


    std::cout << K << " Capping fps to 60...\n";
    window.setFramerateLimit(60); //cap fps to 60

    sf::Clock clock;
    sf::Time elapsed;


    std::cout << K << " Success, have a nice time gaming!\n";

    // pad 1
    sf::RectangleShape pad1(sf::Vector2f(10, 100.f));
    pad1.setPosition(0.f, 250.f);
    pad1.setFillColor(sf::Color(255, 153, 255));

    //pad2
    sf::RectangleShape pad2(sf::Vector2f(10.f, 100.f));
    pad2.setPosition(790.f, 250.f);
    pad2.setFillColor(sf::Color(102, 178, 255));

    //ball
    sf::RectangleShape ball(sf::Vector2f(5.f, 5.f));
    ball.setPosition(400.f, 300.f);
    ball.setFillColor(sf::Color::Black);

    sf::Vector2f ballVelocity(5.0f, 3.0f); //declaire ball velosity 

    GameState gameState = Start;

    int pointsP1 = 0;
    int pointsP2 = 0;

    while (window.isOpen()) //game loop
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { //close window if user tries to quit it
                std::cout << K << " Destroying window...\n";
                window.close();
            }
        }



        window.clear(sf::Color(153, 255, 153)); //make window green

        if (gameState == Start) {
            drawText(window, "Welcome", 250, 50, 70);
            drawText(window, "Press Enter to start the game at NORMAL mode!", 20, 200, 33);
            drawText(window, "Press SPACE to start the game at HARD mode!", 20, 350, 35);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                gameState = PlayingEasy;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                gameState = PlayingHard;
            }
        }
        else if (gameState == PlayingEasy) {
            handleGameLogicEasy(pad1, pad2, ball, window, ballVelocity, gameState, pointsP1, pointsP2);

            drawPad1(window, pad1);
            drawPad2(window, pad2);
            drawBall(window, ball);
            drawText(window, std::to_string(pointsP1), 3, 0, 60);
            drawText(window, std::to_string(pointsP2), 765, 0, 60);
            elapsed = clock.restart();
            int fps = 1.0f / elapsed.asSeconds();
            drawText(window, "FPS: " + std::to_string(fps), 310, 0, 20);
        }
        else if (gameState == PlayingHard) {
            handleGameLogicHard(pad1, pad2, ball, window, ballVelocity, gameState, pointsP1, pointsP2);

            drawPad1(window, pad1);
            drawPad2(window, pad2);
            drawBall(window, ball);
            drawText(window, std::to_string(pointsP1), 3, 0, 60);
            drawText(window, std::to_string(pointsP2), 765, 0, 60);
            elapsed = clock.restart();
            int fps = 1.0f / elapsed.asSeconds();
            drawText(window, "FPS: " + std::to_string(fps), 310, 0, 20);
        }
        else if (gameState == WinPlayer1) {
            drawText(window, "WINNER : PLAYER 1", 150, 230, 60);
            drawText(window, "Press G to restart", 150, 380, 60);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                pointsP1 = 0;
                pointsP2 = 0;
                gameState = Start;
            }
        }
        else if (gameState == WinPlayer2) {
            drawText(window, "WINNER : PLAYER 2", 150, 230, 60);
            drawText(window, "Press G to restart", 150, 380, 60);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                pointsP1 = 0;
                pointsP2 = 0;
                gameState = Start;
            }
        }

        window.display(); //update display
    }

    std::cout << K << " Bye! :)\n";

    return 0;
}

