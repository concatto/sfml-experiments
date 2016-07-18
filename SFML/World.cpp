/*
 * World.cpp
 *
 *  Created on: Jul 6, 2016
 *      Author: concatto
 */

#include "World.h"
#include <algorithm>

World::World() : vertices(sf::Quads)
{

}

World::World(sf::Texture* texture, std::vector<std::string> map, sf::Vector2f tileSize) : World() {
    create(texture, map, tileSize);
}

void World::create(sf::Texture* texture, std::vector<std::string> map, sf::Vector2f tileSize)
{
    this->texture = texture;
    this->tileSize = tileSize;

    float w = tileSize.x;
    float h = tileSize.y;

    for (unsigned int i = 0; i < map.size(); i++) {
        std::string& row = map[i];
        std::vector<TileType> tileRow;
        if (row.size() > columns) {
            columns = row.size();
        }

        for (unsigned int j = 0; j < row.size(); j++) {
            int type = row[j] - '0';
            tileRow.push_back(type < 2 ? TileType::Collidable : TileType::Regular);

            //sf::Color color = tileRow.back() == TileType::Regular ? sf::Color::Green : sf::Color::Red;

            vertices.append(sf::Vertex(sf::Vector2f(j * w, i * h), sf::Vector2f(type * w, 0)));
            vertices.append(sf::Vertex(sf::Vector2f((j + 1) * w, i * h), sf::Vector2f((type + 1) * w, 0)));
            vertices.append(sf::Vertex(sf::Vector2f((j + 1) * w, (i + 1) * 32), sf::Vector2f((type + 1) * w, h)));
            vertices.append(sf::Vertex(sf::Vector2f(j * w, (i + 1) * h), sf::Vector2f(type * w, h)));
        }
        tiles.push_back(tileRow);
    }
}

sf::Vector2f World::getTileSize() const
{
    return tileSize;
}

World::TileType World::getTileType(int x, int y) const
{
    y = std::min(getRowCount() - 1, std::max(0, y));
    x = std::min(getColumnCount() - 1, std::max(0, x));
    return tiles[y][x];
}

int World::getRowCount() const
{
    return tiles.size();
}

int World::getColumnCount() const
{
    return columns;
}

sf::Vector2i World::toTileCoordinates(sf::Vector2f point) const
{
    return sf::Vector2i(point.x / tileSize.x, point.y / tileSize.y);
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = texture;
	target.draw(vertices, states);

    /*for (unsigned int i = 0; i < tiles.size(); i++) {
		for (unsigned int j = 0; j < tiles[i].size(); j++) {
			sf::Uint8 value = tiles[i][j];

			sf::RectangleShape rect(tileSize);
			rect.setPosition(j * tileSize.x, i * tileSize.y);
			rect.setFillColor(sf::Color::Transparent);
			rect.setOutlineColor(value == 0 ? sf::Color::Red : sf::Color::Green);
			rect.setOutlineThickness(2);

			target.draw(rect, sf::RenderStates());
		}
    }*/
}
