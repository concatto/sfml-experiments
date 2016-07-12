#include "SFML/Graphics.hpp"
#include "Character.h"
#include "ParticleEmitter.h"
#include "Utility.h"
#include "World.h"
#include "MovementManager.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

std::vector<std::string> generateLevel(int rows, int columns) {
    std::vector<std::string> level;

    int terrainLine = rows * 0.7;

    for (int k = 0; k < rows; k++) {
        std::string row = "";
        for (int i = 0; i < columns; i++) {
            if (k > terrainLine) {
                row.push_back('1');
            } else if (k == terrainLine) {
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

    return level;
}

bool viewWithinBounds(const World& world, const Character& c, View& view) {
    sf::Vector2u center = c.getCenter();
    sf::Vector2f tileSize = world.getTileSize();

}

void moveIfPressed(sf::View& view, sf::Keyboard::Key key, float x, float y) {
    if (sf::Keyboard::isKeyPressed(key)) {
        view.move(x, y);
    }
}

void centerWindow(sf::Window& window) {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2u windowSize = window.getSize();
    window.setPosition(sf::Vector2i((desktop.width / 2.0) - (windowSize.x / 2.0), (desktop.height / 2.0) - (windowSize.y / 2.0)));
}

int main() {
	std::srand(std::time(nullptr));

	const int width = 1024;
	const int height = 768;

	sf::RenderWindow window(sf::VideoMode(width, height), "SFML");
    window.setFramerateLimit(60);
    centerWindow(window);

	sf::Texture tileset;
	tileset.loadFromFile("TileFrames.png");

    sf::Vector2u windowSize = window.getSize();
    sf::View view(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0), sf::Vector2f(windowSize.x, windowSize.y));

    std::vector<std::string> level = generateLevel(25, 100);

	World world(tileset, level, sf::Vector2f(32, 32));

	sf::Texture tex;
	tex.loadFromFile("walk.png");

    Character c(tex, sf::Vector2u(26, 40));
    c.setPosition(100, 360);

    MovementManager movement(world, c);

	sf::RenderTexture buffer;
    buffer.create(width, height);

	sf::RenderTexture buffer2;
	buffer2.create(width, height);

	ParticleEmitter emitter(9000);

    sf::Shader shader;
    //shader.loadFromFile("glow.frag", sf::Shader::Fragment);
    shader.setParameter("texture", sf::Shader::CurrentTexture);
    shader.setParameter("step", sf::Vector2f(1.0 / width, 1.0 / height));

    sf::Clock clock;

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


        float deltaTime = clock.restart().asMilliseconds() * 0.06;
        movement.update(deltaTime);
        c.update();
		emitter.update();
		emitter.setOrigin(c.getPosition());
        emitter.setInvert(!c.isFacingRight());

        if (viewWithinBounds(world, c, view)) {
            view.setCenter(c.getBoundingBox().left, c.getBoundingBox().top);
        }

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
        //window.draw(sf::Sprite(buffer.getTexture()), sf::RenderStates(&shader));
		window.draw(c);
		c.draw(window);

		window.display();
	}

	return 0;
}
