#ifndef GAME_H
#define GAME_H

#include "Updatable.h"
#include "Character.h"
#include "World.h"
#include "MovementManager.h"
#include <SFML/Graphics.hpp>

class Game : public Updatable
{
private:
    sf::RenderWindow& window;
    sf::View view;
    sf::Texture tileset;
    sf::Texture characterTexture;
    World world;
    Character character;
    MovementManager movement;

    void handleKeyboard();
    void updateView();
    void updateObjects();

    static std::vector<std::string> generateLevel(int rows, int columns);
public:
    Game(sf::RenderWindow& window);

    virtual void update() override;

};

#endif // GAME_H
