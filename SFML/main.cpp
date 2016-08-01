#include "SFML/Graphics.hpp"
#include "Character.h"
#include "ParticleEmitter.h"
#include "Beta/ParticleEmitter2.h"
#include "Utility.h"
#include "World.h"
#include "MovementManager.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <utility>
#include <functional>
#include "Game.h"


void clampView(const World& world, sf::View& view) {
    sf::Vector2f halfSize = sf::Vector2f(view.getSize().x / 2.0, view.getSize().y / 2.0);
    sf::Vector2f tileSize = world.getTileSize();
    sf::Vector2f center = view.getCenter();
    float y = std::min((world.getRowCount() * tileSize.y) - halfSize.y, std::max(halfSize.y, center.y));
    float x = std::min((world.getColumnCount()* tileSize.x) - halfSize.x, std::max(halfSize.x, center.x));

    view.setCenter(x, y);
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

    //ParticleEmitter emitter(9000);

    sf::Shader shader;
    shader.loadFromFile("glow.frag", sf::Shader::Fragment);
    shader.setParameter("texture", sf::Shader::CurrentTexture);
    shader.setParameter("step", sf::Vector2f(width, height));

    sf::RenderTexture firstTex;
    firstTex.create(width, height);

    sf::RenderTexture secondTex;
    secondTex.create(width, height);

    sf::Clock clock;
    Game game(window);

    //std::vector<std::reference_wrapper<Updatable>> updatables{movement, c, emitter};

    ParticleEmitter2 emitter(2000);
    ParticleEmitter2 emitter2(3000);
    ParticleEmitter2 emitter3(2000);
    emitter.start();
    emitter2.start();
    emitter3.start();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

        emitter.setActive(sf::Keyboard::isKeyPressed(sf::Keyboard::Space));
        emitter2.setActive(sf::Keyboard::isKeyPressed(sf::Keyboard::O));
        emitter3.setActive(sf::Keyboard::isKeyPressed(sf::Keyboard::P));

        //game.update();
        emitter.setOrigin(sf::Vector2f(300, 600));
        emitter.update();
        emitter2.setOrigin(sf::Vector2f(500, 600));
        emitter2.update();
        emitter3.setOrigin(sf::Vector2f(700, 600));
        emitter3.update();

        /*firstTex.clear(sf::Color::Transparent);
        firstTex.draw(emitter);
        firstTex.display();

        shader.setParameter("direction", sf::Vector2f(1, 0));

        secondTex.clear(sf::Color::Transparent);
        secondTex.draw(sf::Sprite(firstTex.getTexture()));
        secondTex.display();

        shader.setParameter("direction", sf::Vector2f(0, 1));
        */
        window.clear();
        //window.draw(sf::Sprite(secondTex.getTexture()));
        window.draw(emitter);
        window.draw(emitter2);
        window.draw(emitter3);
        window.display();

        /*
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

        for (Updatable& upd : updatables) {
            upd.update();
        }

		emitter.setOrigin(c.getPosition());
        emitter.setInvert(!c.isFacingRight());
        view.setCenter(c.getBoundingBox().left, c.getBoundingBox().top);
        clampView(world, view);

		window.clear();
		window.setView(view);
        window.draw(world);

		buffer.clear(sf::Color::Transparent);
		buffer.draw(emitter);
		buffer.display();

		shader.setParameter("direction", sf::Vector2f(1, 0));
		buffer2.clear(sf::Color::Transparent);
		buffer2.draw(sf::Sprite(buffer.getTexture()), sf::RenderStates(&shader));
        buffer2.display();

		shader.setParameter("direction", sf::Vector2f(0, 1));
        //window.draw(sf::Sprite(buffer.getTexture()), sf::RenderStates(&shader));
		window.draw(c);
		c.draw(window);

        window.display();*/
	}

	return 0;
}
