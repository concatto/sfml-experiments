#include "SFML/Graphics.hpp"
#include "Character.h"
#include "ParticleEmitter.h"
#include "Utility.h"
#include "World.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>

//enum Direction {Up, Down, Left, Right};

void moveIfPressed(sf::View& view, sf::Keyboard::Key key, float x, float y) {
	if (sf::Keyboard::isKeyPressed(key)) {
		view.move(x, y);
	}
}

int raycastDown(const World& world, sf::Vector2f point) {
    sf::Vector2f tileSize = world.getTileSize();

    int x = point.x / tileSize.x;
    int y = point.y / tileSize.y;

    for (unsigned int i = y; i < world.getRowCount(); i++) {
        if (world.getTileType(i, x) == World::Collidable) {
            return (i * tileSize.y) - (point.y);
        }
    }

    return -1;
}

int raycastUp(const World& world, sf::Vector2f point) {
    sf::Vector2f tileSize = world.getTileSize();

    int x = point.x / tileSize.x;
    int y = point.y / tileSize.y;

    for (int i = y; i >= 0; i--) {
        if (world.getTileType(i, x) == World::Collidable) {
            return (point.y) - ((i + 1) * tileSize.y);
        }
    }

    return point.y;
}


void collide(const World& world, Character& c) {
    sf::IntRect box = c.getBoundingBox();

    int down = raycastDown(world, sf::Vector2f(box.left + (box.width / 2.0), box.top + box.height));
    int up = raycastUp(world, sf::Vector2f(box.left + (box.width / 2.0), box.top));

    c.notifyGroundDistance(down);
    c.notifyCeilingDistance(up);
}


int main() {
	std::srand(std::time(nullptr));

	const int width = 1024;
	const int height = 768;

	sf::RenderWindow window(sf::VideoMode(width, height), "SFML");
	window.setFramerateLimit(60);

	sf::Texture tileset;
	tileset.loadFromFile("TileFrames.png");

	//Centering
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::Vector2u windowSize = window.getSize();
	window.setPosition(sf::Vector2i((desktop.width / 2.0) - (windowSize.x / 2.0), (desktop.height / 2.0) - (windowSize.y / 2.0)));

	double xCenter = windowSize.x / 2.0;
	double yCenter = windowSize.y / 2.0;

	sf::View view(sf::Vector2f(xCenter, yCenter), sf::Vector2f(windowSize.x, windowSize.y));

	std::vector<std::string> level;
	for (int k = 0; k < 24; k++) {
		std::string row = "";
		for (int i = 0; i < 100; i++) {
			if (k > 17) {
				row.push_back('1');
			} else if (k == 17) {
				row.push_back('0');
			} else {
                if (Utility::random() < 0.05) {
                    row.push_back('0');
                } else {
                    row.push_back(static_cast<int>(Utility::random(4, 6) + 0.5) + '0');
                }
			}
		}
		level.push_back(row);
	}

	World world(tileset, level, sf::Vector2f(32, 32));

	sf::Texture tex;
	tex.loadFromFile("walk.png");
	Character c(tex, sf::Vector2u(30, 40));
    c.setPosition(100, 360);

	sf::RenderTexture buffer;
	buffer.create(width, height);

	sf::RenderTexture buffer2;
	buffer2.create(width, height);

	ParticleEmitter emitter(9000);

	sf::Shader shader;
	shader.loadFromFile("glow.frag", sf::Shader::Fragment);
	shader.setParameter("texture", sf::Shader::CurrentTexture);
	shader.setParameter("step", sf::Vector2f(1.0 / width, 1.0 / height));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		moveIfPressed(view, sf::Keyboard::Numpad8, 0, -1);
		moveIfPressed(view, sf::Keyboard::Numpad2, 0, 1);
		moveIfPressed(view, sf::Keyboard::Numpad4, -1, 0);
		moveIfPressed(view, sf::Keyboard::Numpad6, 1, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			view.zoom(0.9);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			view.zoom(1.1);
		}


        collide(world, c);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            c.jump();
        }


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			c.accelerate();
			if (!emitter.isActive()) emitter.start();
		} else {
			c.slow();
			if (emitter.isActive()) emitter.end();
		}

		bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

		if (!(left || right) || (left && right)) {
			c.stand();
		} else if (right) {
			c.moveRight();
		} else if (left) {
			c.moveLeft();
		}

		emitter.update();
		c.update();
		emitter.setOrigin(c.getPosition());
		emitter.setInvert(!c.isFacingRight());

		window.clear();
		window.setView(view);
		window.draw(world);

		buffer.clear(sf::Color::Transparent);
		buffer.draw(emitter);
		buffer.display();
/*
		shader.setParameter("direction", sf::Vector2f(1, 0));
		buffer2.clear(sf::Color::Transparent);
		buffer2.draw(sf::Sprite(buffer.getTexture()), sf::RenderStates(&shader));
		buffer2.display();*/

		shader.setParameter("direction", sf::Vector2f(0, 1));
		window.draw(sf::Sprite(buffer.getTexture()), sf::RenderStates(&shader));
		window.draw(c);
		c.draw(window);

		window.display();
	}

	return 0;
}
