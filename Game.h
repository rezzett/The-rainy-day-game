#pragma once

#include <vector>
#include <iostream>

#include "AssetManager.h"
#include "GameObj.h"
#include "Gui.h"

class Game {
	std::shared_ptr<sf::RenderWindow> win;
	AssetManager assetManager;
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
				std::cout << "Fail. Deep:" << deep << std::endl;
				if (deep > 5) {
					std::cout << "Game Over!" << std::endl;
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
