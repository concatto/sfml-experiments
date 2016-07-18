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
public:
    enum TileType {Collidable, Regular};

private:
    std::vector<std::vector<TileType>> tiles;
    sf::VertexArray vertices = sf::VertexArray(sf::Quads);
    sf::Texture* texture;
	sf::Vector2f tileSize;
    unsigned int columns = 0;

	void createTiles(std::vector<std::string> map);

public:
    World();
    World(sf::Texture* texture, std::vector<std::string> map, sf::Vector2f tileSize);

    void create(sf::Texture* texture, std::vector<std::string> map, sf::Vector2f tileSize);
	sf::Vector2f getTileSize() const;
    TileType getTileType(int x, int y) const;
    int getRowCount() const;
    int getColumnCount() const;
    sf::Vector2i toTileCoordinates(sf::Vector2f point) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif /* WORLD_H_ */
