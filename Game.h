#pragma once

#include <vector>
#include <iostream>

#include "AssetManager.h"
#include "GameObj.h"
#include "Gui.h"

class Game {
	// TODO water layer
	// TODO sounds manager
	std::shared_ptr<sf::RenderWindow> win;
	AssetManager assetManager;
	sf::RectangleShape water;
	Gui gui;
	Bucket bucket;
	sf::Sprite bg;
	std::vector<Drop> drops;
	float dropSpawnDelay{ 800 };
	float dropTimer{ 0 };
	int dropLimit{ 5 };
	int score{ 0 };
	int deep{ 0 };
	bool isGameOver{ false };

	void spawnDrop()
	{
		if (drops.size() < dropLimit) {
			if (dropTimer > dropSpawnDelay) {
				Drop d;
				d.setTexture(assetManager.getTexture("assets/drop.png"));
				d.setPosition(rand() % (int)(win->getSize().x - d.getGlobalBounds().width), 0.);
				drops.push_back(d);
				dropTimer = 0.0;
			}
		}
	}
public:
	Game(AssetManager&& assets) : assetManager(assets)
	{
		win = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "Rainy Day");
		win->setFramerateLimit(2000); // TODO
		bg.setTexture(assetManager.getTexture("assets/rainbg.png"));
		bg.setScale(4.0, 4.0);
		gui.setup(*win);

		water.setFillColor(sf::Color(0, 150, 255, 128));
		water.setSize(sf::Vector2f(win->getSize().x, 100));
		water.setPosition(0, win->getSize().y);


		bucket.setTexture(assetManager.getTexture("assets/bucket.png"));
		bucket.setPosition(
			win->getSize().x / 2.0 - bucket.getGlobalBounds().width / 2,
			(win->getSize().y - bucket.getGlobalBounds().height));
	}

	void update() {
		dropTimer += 0.1;
		spawnDrop();
		for (int i = 0; i < drops.size(); ++i) drops[i].update(*win);
		bucket.update(*win);
		//check col
		for (int i = 0; i < drops.size(); ++i) {
			if (drops[i].getGlobalBounds().intersects(bucket.getGlobalBounds())) {
				drops.erase(drops.begin() + i);
				score++;
				dropSpawnDelay -= (int)(score / 4); // difficulty
			}
		}

		gui.update(score);

		for (int i = 0; i < drops.size(); ++i) {
			if (drops[i].getGlobalBounds().top > win->getSize().y) {
				drops.erase(drops.begin() + i);
				deep++;
				water.setPosition(0, win->getSize().y - deep);
				if (deep > bucket.getGlobalBounds().height - 10) {
					isGameOver = true;
				}
			}
		}
	}

	void draw() {
		win->clear();
		win->draw(bg);
		gui.render(*win, isGameOver);
		for (int i = 0; i < drops.size(); ++i) drops[i].render(*win);
		bucket.render(*win);
		win->draw(water);
		win->display();
	}

	void run() {
		while (win->isOpen())
		{
			sf::Event e;
			while (win->pollEvent(e))
			{
				if (e.type == sf::Event::Closed) win->close();
			}

			if (!isGameOver) {
				update();
			}
			draw();
		}
	}
};
