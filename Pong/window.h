#pragma once
#include<SFML/Graphics.hpp>
#include "game.h"
class window
{
public:
	window(sf::Vector2u winSize, unsigned int framerateCap, std::uint32_t Style);
	~window() = default;
	void mainLoop();
	sf::Vector2u getWindowPos() { return this->windowSize; }

private:
	sf::Vector2u windowSize;
	int frameRateCap;
	sf::RenderWindow myWIn;
	std::uint32_t Style;
	game myGame;
};

