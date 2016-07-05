#include "SFML/Graphics.hpp"
#include "Character.h"
#include "ParticleEmitter.h"
#include "Utility.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

sf::Color randomColor() {
	std::vector<sf::Color> colors{sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Cyan, sf::Color::Yellow, sf::Color::Magenta};

	return colors[std::rand() % colors.size()];
}

sf::VertexArray createWorld(const std::string& world, int columns) {
	sf::VertexArray vertices(sf::Quads, world.size() * 4);
	int rows = world.size() / columns;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			int idx = i * columns + j;

			int type = world[idx] - '0';
			int v = idx * 4;

			vertices[v + 0].position = sf::Vector2f(j * 32, i * 32);
			vertices[v + 1].position = sf::Vector2f((j + 1) * 32, i * 32);
			vertices[v + 2].position = sf::Vector2f((j + 1) * 32, (i + 1) * 32);
			vertices[v + 3].position = sf::Vector2f(j * 32, (i + 1) * 32);

			vertices[v + 0].texCoords = sf::Vector2f(type * 32, 0);
			vertices[v + 1].texCoords = sf::Vector2f((type + 1) * 32, 0);
			vertices[v + 2].texCoords = sf::Vector2f((type + 1) * 32, 32);
			vertices[v + 3].texCoords = sf::Vector2f(type * 32, 32);
		}
	}

	return vertices;
}

void moveIfPressed(sf::View& view, sf::Keyboard::Key key, float x, float y) {
	if (sf::Keyboard::isKeyPressed(key)) {
		view.move(x, y);
	}
}

int main() {
	std::srand(std::time(nullptr));

	sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML");
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

	std::string level = "";
	for (int k = 0; k < 24; k++) {
		for (int i = 0; i < 100; i++) {
			if (k > 17) {
				level.push_back('1');
			} else if (k == 17) {
				level.push_back('0');
			} else {
				level.push_back(static_cast<int>(Utility::random(4, 6) + 0.5) + '0');
			}
		}
	}

	sf::VertexArray world = createWorld(level, 100);
	sf::RenderStates states(&tileset);

	sf::Texture tex;
	tex.loadFromFile("walk.png");
	Character c(tex);
	c.setPosition(100, 460);
	c.walk();

	sf::RenderTexture buffer;
	buffer.create(1024, 768);

	ParticleEmitter emitter(10000);

	sf::Shader shader;
	shader.loadFromFile("glow.frag", sf::Shader::Fragment);
	shader.setParameter("texture", sf::Shader::CurrentTexture);
	shader.setParameter("step", sf::Vector2f(1.0 / window.getSize().x, 1.0 / window.getSize().y));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		moveIfPressed(view, sf::Keyboard::Num8, 0, -1);
		moveIfPressed(view, sf::Keyboard::Num2, 0, 1);
		moveIfPressed(view, sf::Keyboard::Num4, -1, 0);
		moveIfPressed(view, sf::Keyboard::Num6, 1, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			view.zoom(0.9);
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			view.zoom(1.1);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			c.accelerate();
			if (!emitter.isActive()) emitter.start();
		} else {
			c.slow();
			if (emitter.isActive()) emitter.end();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			c.moveRight();
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			c.moveLeft();
		}

		window.clear();
		window.setView(view);
		window.draw(world, states);


		buffer.clear(sf::Color::Transparent);
		buffer.draw(emitter);
		buffer.display();

		window.draw(sf::Sprite(buffer.getTexture()), sf::RenderStates(&shader));
		window.draw(c);

		emitter.update();
		c.update();
		emitter.setOrigin(c.getPosition() + sf::Vector2f(68, 48));
		window.display();
	}

	return 0;
}
