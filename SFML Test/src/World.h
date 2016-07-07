/*
 * World.h
 *
 *  Created on: Jul 6, 2016
 *      Author: concatto
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <SFML/Graphics.hpp>
#include <vector>

class World : public sf::Drawable, public sf::Transformable {
	std::vector<std::vector<sf::Uint8>> tiles;
	sf::VertexArray vertices;
	const sf::Texture& texture;
	sf::Vector2f tileSize;

	void createTiles(std::vector<std::string> map);

public:
	World(const sf::Texture& texture, std::vector<std::string> map, sf::Vector2f tileSize);

	sf::Vector2f getTileSize() const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* WORLD_H_ */
