#include "MovementManager.h"
#include <limits>
#include <iostream>

MovementManager::MovementManager(const World& world, Character& character) : world(world), character(character) {

}

void MovementManager::update() {
    float verticalMovement = character.getVerticalForce();

    int up = calculateDistance(character, Up) - 1;
    if (up <= verticalMovement) {
        character.move(0, -up);
        character.setVerticalForce(0);
        verticalMovement = character.getVerticalForce();
    }

    int down = calculateDistance(character, Down) - 1;
    if (down <= -verticalMovement) {
        character.move(0, down);
        character.setState(Character::Ground);
        character.setVerticalForce(0);
    } else {
        if (character.getState(Character::Ground)) {
            character.unsetState(Character::Ground);
        }

        character.move(0, -verticalMovement);
        character.setVerticalForce(verticalMovement - Gravity);
    }

    if (character.getState(Character::Walk)) {
        int horizontalDistance = calculateDistance(character, character.isFacingRight() ? Right : Left) - 1;
        int coefficient = character.isFacingRight() ? 1 : -1;

        float movement = character.getMovementSpeed();
        if (horizontalDistance < movement) {
            character.move(horizontalDistance * coefficient, 0);
        } else {
            character.move(movement * coefficient, 0);
        }
    }
}


int MovementManager::calculateDistance(const Character& c, Direction direction) {
    sf::Vector2f tileSize = world.getTileSize();
    sf::IntRect box = c.getBoundingBox();

    int length = (direction == Left || direction == Right) ? box.height : box.width;
    int points = std::ceil(length / tileSize.y) + 1;

    for (int i = 0; i <= points; i++) {
        float delta = i * (length / static_cast<float>(points));
        sf::Vector2i coords = world.toTileCoordinates(boundingBoxPoint(box, delta, direction));
        sf::Vector2i offset = directionOffset(direction);

        if (world.getTileType(coords.x + offset.x, coords.y + offset.y) == World::Collidable) {
            return distance(coords, tileSize, box, direction);
        }
    }

    return std::numeric_limits<int>::max();
}
/*

int leftDistance(Character& c) {
    sf::Vector2f tileSize = world.getTileSize();
    sf::IntRect box = c.getBoundingBox();
    int points = std::ceil(box.height / tileSize.y) + 1;

    for (int i = 0; i <= points; i++) {
        float delta = i * (box.height / static_cast<float>(points));
        sf::Vector2i coords = world.toTileCoordinates(sf::Vector2f(box.left, box.top + delta - 1));

        if (world.getTileType(coords.x - 1, coords.y) == World::Collidable) {
            return box.left - (coords.x * tileSize.x);
        }
    }

    return box.left;
}

int upDistance(const World& world, Character& c) {
    sf::Vector2f tileSize = world.getTileSize();
    sf::IntRect box = c.getBoundingBox();
    int points = std::ceil(box.width / tileSize.y) + 1;

    for (int i = 0; i <= points; i++) {
        float delta = i * (box.width / static_cast<float>(points));
        sf::Vector2i coords = world.toTileCoordinates(sf::Vector2f(box.left + delta, box.top));

        if (world.getTileType(coords.x, coords.y - 1) == World::Collidable) {
            return box.top - (coords.y * tileSize.y);
        }
    }

    return box.top;
}

int downDistance(const World& world, Character& c) {
    sf::Vector2f tileSize = world.getTileSize();
    sf::IntRect box = c.getBoundingBox();
    int points = std::ceil(box.width / tileSize.y) + 1;

    for (int i = 0; i <= points; i++) {
        float delta = i * (box.width / static_cast<float>(points));
        sf::Vector2i coords = world.toTileCoordinates(sf::Vector2f(box.left + delta, box.top + box.height - 1));

        if (world.getTileType(coords.x, coords.y + 1) == World::Collidable) {
            return ((coords.y + 1) * tileSize.y) - (box.top + box.height);
        }
    }

    return std::numeric_limits<int>::max();
}*/


sf::Vector2i MovementManager::directionOffset(Direction direction) {
    switch (direction) {
        case Up: return sf::Vector2i(0, -1);
        case Down: return sf::Vector2i(0, +1);
        case Left: return sf::Vector2i(-1, 0);
        case Right: return sf::Vector2i(+1, 0);
    }

    return sf::Vector2i();
}

sf::Vector2f MovementManager::boundingBoxPoint(sf::IntRect box, float delta, Direction direction) {
    switch (direction) {
        case Up:
            return sf::Vector2f(box.left + delta, box.top);
        case Down:
            return sf::Vector2f(box.left + delta, box.top + box.height);
        case Left:
            return sf::Vector2f(box.left, box.top + delta);
        case Right:
            return sf::Vector2f(box.left + box.width, box.top + delta);
    }

    return sf::Vector2f();
}

float MovementManager::distance(sf::Vector2i coords, sf::Vector2f tileSize, sf::IntRect box, Direction direction) {
    switch (direction) {
        case Up:
            return box.top - (coords.y * tileSize.y);
        case Down:
            return ((coords.y + 1) * tileSize.y) - (box.top + box.height);
        case Left:
            return box.left - (coords.x * tileSize.x);
        case Right:
            return ((coords.x + 1) * tileSize.x) - (box.left + box.width);
    }

    return 0;
}
