#pragma once

#include <SFML/Graphics.hpp>
#include <fmt/core.h>

class Gui
{
	sf::Font font;
	sf::Text score;
	sf::Text gameOver;
	sf::Text playAgain;
public:
	void setup(const sf::RenderWindow& win)
	{
		if (!font.loadFromFile("assets/ACLine.otf")) throw std::exception("Failed to load font");
		score.setFont(font);
		score.setPosition(10, 10);
		score.setCharacterSize(18);
		score.setStyle(sf::Text::Bold);
		score.setString("Score: 0");

		gameOver.setFont(font);
		gameOver.setString("GAME OVER!");
		gameOver.setStyle(sf::Text::Bold);
		gameOver.setCharacterSize(40);
		gameOver.setFillColor(sf::Color::Red);
		gameOver.setPosition(win.getSize().x / 2 - (gameOver.getGlobalBounds().width / 2)
			, win.getSize().y / 2 - (gameOver.getGlobalBounds().height / 2) - 100);

		playAgain.setFont(font);
		playAgain.setCharacterSize(24);
		gameOver.setStyle(sf::Text::Bold);
		playAgain.setString("Play Agian? (Y/N)");
		playAgain.setFillColor(sf::Color::Green);
		playAgain.setPosition(win.getSize().x / 2 - (playAgain.getGlobalBounds().width / 2)
			, win.getSize().y / 2);
	}

	void update(int newScore)
	{
		score.setString(fmt::format("Score: {}", newScore));
	}

	void render(sf::RenderTarget& target, bool isGameOver)
	{
		if (isGameOver) {
			target.draw(gameOver);
			target.draw(playAgain);
		}
		target.draw(score);
	}
};
