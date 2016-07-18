#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H

#include "Character.h"
#include "Updatable.h"
#include "World.h"
#include <SFML/Graphics.hpp>

class MovementManager : public Updatable
{
    const float Gravity = 0.5;
    enum Direction {Up, Down, Left, Right};
    const World& world;
    Character& character;

public:
    MovementManager(const World& world, Character& character);

    virtual void update() override;
    void moveCharacter(Character& character, float distance, Direction direction);
private:
    static inline float distance(sf::Vector2i coords, sf::Vector2f tileSize, sf::IntRect box, Direction direction);
    static inline sf::Vector2f boundingBoxPoint(sf::IntRect box, float delta, Direction direction);
    static inline sf::Vector2i directionOffset(Direction direction);
    int calculateDistance(const Character& c, Direction direction);
};

#endif // MOVEMENTMANAGER_H
