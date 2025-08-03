#include "game.h"
#include <SFML/Graphics.hpp>
#include <iostream>


game::game(sf::Vector2f ballVelocity)  
: ballVelocity(ballVelocity), // Correctly initialize ballVelocity  
  pointsP1(0),  
  pointsP2(0),  
  state(Start)
{  
this->audio = Audio();  
if (!this->font.openFromFile("SweetieBubbleGum-Regular.ttf"))  
{  
	std::cerr << "couldn't open font file :(\n";  
}  
WelcomeText = createText("Welcome to Pong", 60, sf::Color::Black, {250, 100});  
PlayHardText = createText("Press Enter to start the game at HARD mode!", 33, sf::Color::Black, {20, 200});  
PlayEasyText = createText("Press SPACE to start the game at EASY mode!", 35, sf::Color::Black, {20, 350});  

this->pad1 = createRect({10, 100}, {0, 250}, sf::Color(255, 178, 255));  
this->pad2 = createRect({10, 100}, {790, 250}, sf::Color(255, 153, 255));  
this->ball = createRect({10, 10}, {400, 300}, sf::Color::Black);  
}

void game::drawStart(sf::RenderWindow& wnd)
{
	wnd.draw(*WelcomeText);
	wnd.draw(*PlayHardText);
	wnd.draw(*PlayEasyText);
}

void game::handleGameStates(sf::RenderWindow& window)
{
	drawStart(window);
	if (state == Start)
	{

		// Wait for player input to choose difficulty
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
		{
			state = PlayingHard;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			state = PlayingEasy;
		}
	}
	else if (state == PlayingEasy)
	{
		this->gameLogic(5);
		this->GameDrawer(window);
	}
	else if (state == PlayingHard) {
		this->gameLogic(2);
		this->GameDrawer(window);
	}
	else if (state == WinPlayer1)
	{
		this->wonGame(true, window);

	}
	else if (state == WinPlayer2) {
		this->wonGame(false, window);
	}
}




sf::RectangleShape game::createRect(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
	sf::RectangleShape pad(size);
	pad.setPosition(position);
	pad.setFillColor(color);
	return sf::RectangleShape();
}

std::unique_ptr<sf::Text> game::createText(sf::String txt, unsigned int fontSize, sf::Color color, sf::Vector2f position) const {
	auto text = std::make_unique<sf::Text>(this->font, txt, fontSize);
	text->setFillColor(color);
	text->setPosition(position);
	return text;
}

void game::gameLogic(float ballVelocity)
{
	float pad1y = this->pad1.getPosition().y;
	float pad2y = this->pad2.getPosition().y;

	//pad1 controller
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		if (pad1y != 0) {
			this->pad1.setPosition({ this->pad1.getPosition().x, pad1y - ballVelocity });
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		if (pad1y != 500) {
			this->pad1.setPosition({ this->pad1.getPosition().x, pad1y + ballVelocity });
		}
	}

	//pad2 controller
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
		if (pad2y != 0) {
			this->pad1.setPosition({ this->pad2.getPosition().x, pad2y - ballVelocity });
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
		if (pad2y != 500) {
			this->pad1.setPosition({ this->pad2.getPosition().x, pad2y + ballVelocity });
		}
	}

	ball.move(this->ballVelocity);

	//ball counter
	if (this->ball.getPosition().x <= 0) {
		this->audio.getSoundWallHit().play();
		this->pointsP2++;
		this->TextPointsP2 = createText(std::to_string(pointsP2), 60, sf::Color::Black, { 765,0 });
		std::cout << "player 2 scored\n";
		this->resetBall();
	}
	else if (this->ball.getPosition().x >= 800 - ball.getSize().x) {
		this->audio.getSoundWallHit().play();
		this->pointsP1++;
		this->TextPointsP1 = createText(std::to_string(pointsP1), 60, sf::Color::Black, { 3,0 });
		std::cout << "player2 scored!\n";
		this->resetBall();
	}
	else if (ball.getPosition().y <= 0 || ball.getPosition().y >= 600 - ball.getSize().y) {
		this->ballVelocity.y = this->turnToNegative(this->ballVelocity.y);
		this->audio.getSoundHit().play();
	}
	else if (ball.getGlobalBounds().findIntersection(pad1.getGlobalBounds()) || ball.getGlobalBounds().findIntersection(pad2.getGlobalBounds())) {
		this->ballVelocity.x = this->turnToNegative(this->ballVelocity.x);
		this->audio.getSoundHit().play();
	}

	if (this->pointsP1 == 10) {
		this->state = WinPlayer2;
	}

	if (pointsP2 == 10) {
		this->state = WinPlayer1;
	}
	

}

void game::GameDrawer(sf::RenderWindow& window)
{
	window.draw(this->pad1);
	window.draw(this->pad2);
	window.draw(this->ball);
	window.draw(*this->TextPointsP1);
	window.draw(*this->TextPointsP2);
	window.draw(this->pad1);
	window.draw(this->pad1);
}

void game::wonGame(bool isPlayer1, sf::RenderWindow& wnd)
{
	this->audio.StopMusicAndLoop();
	this->audio.getSoundEnd().play();
	this->WordWinnerText = createText("WINNER : ", 60, sf::Color::Black, { 220, 230 });
	this->RestartText = createText("Press G to restart", 60, sf::Color::Black, { 150, 380 });
	if (isPlayer1) {
		this->winnerText = createText("WINNER : LIA", 60, sf::Color(255, 153, 255), { 220, 230 });
		wnd.draw(*this->RestartText);
	}
	else {
		this->winnerText = createText("WINNER : KYRMA", 60, sf::Color(102, 178, 255), { 170, 230 });
		wnd.draw(*this->RestartText);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) {
		this->pointsP1 = 0;
		this->pointsP2 = 0;
		this->state = Start;
	}
}
