#include "Game.h"
#include "Utility.h"

Game::Game(sf::RenderWindow &window) : window(window), view(), world(), character(), movement(world, character)
{
    tileset.loadFromFile("TileFrames.png");
    characterTexture.loadFromFile("walk.png");

    world.create(&tileset, generateLevel(30, 200), sf::Vector2f(32, 32));
    character.setTexture(characterTexture);
    character.setSizeBounds(sf::Vector2u(26, 40));
    character.setPosition(300, 160);

    sf::Vector2u windowSize = window.getSize();
    view.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    view.setCenter(sf::Vector2f(windowSize.x / 2.0, windowSize.y / 2.0));
}

void Game::update()
{
    handleKeyboard();
    updateObjects();
    updateView();

    window.clear();
    window.setView(view);
    window.draw(world);
    window.draw(character);
    window.display();
}

void Game::handleKeyboard()
{
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);

    if (!(left || right) || (left && right)) {
        character.stand();
    } else if (right) {
        character.moveRight();
    } else if (left) {
        character.moveLeft();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        character.jump();
    }
}

void Game::updateView()
{
    sf::IntRect boundingBox = character.getBoundingBox();
    float x = boundingBox.left + (boundingBox.width / 2.0);
    float y = boundingBox.top + (boundingBox.height / 2.0);

    sf::Vector2f viewSize = view.getSize();
    sf::Vector2f tileSize = world.getTileSize();
    sf::Vector2f halfSize = sf::Vector2f(viewSize.x / 2.0, viewSize.y / 2.0);

    x = std::min((world.getColumnCount()* tileSize.x) - halfSize.x, std::max(halfSize.x, x));
    y = std::min((world.getRowCount() * tileSize.y) - halfSize.y, std::max(halfSize.y, y));

    view.setCenter(x, y);
}

void Game::updateObjects()
{
    character.update();
    movement.update();
}

std::vector<std::string> Game::generateLevel(int rows, int columns) {
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
