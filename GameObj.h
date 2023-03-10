#pragma once

#include <SFML/Graphics.hpp>

class GameObj
{
protected:
	sf::Sprite sprite;
public:
	void setTexture(const sf::Texture& texture)
	{
		sprite.setTexture(texture);
		sprite.setScale(1.5, 1.5);
	}

	void render(sf::RenderTarget& target)
	{
		target.draw(sprite);
	}

	void setPosition(float x, float y)
	{
		sprite.setPosition(x, y);
	}

	sf::FloatRect getGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}


};

class Bucket final : public GameObj
{
public:
	void update(const sf::RenderWindow& win)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and sprite.getPosition().x > 0) {
			sprite.move(-0.1, 0.0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			and sprite.getPosition().x + sprite.getGlobalBounds().width < win.getSize().x)
		{
			sprite.move(0.1, 0.0);
		}
	}
};

class Drop final : public GameObj
{
public:
	void update(const sf::RenderWindow& win)
	{
		sprite.move(0.0, 0.1);
	}
};
