#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "AnimationManager.h"
#include <SFML/Graphics.hpp>

class Character : public sf::Sprite {
private:
	enum Speed {Fast = 10, Normal = 2};

    sf::Uint32 state = 0;
    bool facingRight = true;
    float movementSpeed = Normal;
    float verticalForce = 0;
    sf::Vector2u sizeBounds;
    AnimationManager animationManager;

    void walk();

public:
    enum State {Temp = 0, Stand = 1, Walk = 2, Ground = 4};

	Character(const sf::Texture& texture, sf::Vector2u sizeBounds);

	void update();
	void accelerate();
	void slow();
	void moveLeft();
	void moveRight();
	void stand();
    void jump();
	bool isFacingRight() const;
	bool isMoving() const;
    float getVerticalForce() const;
    float getMovementSpeed() const;
    void setVerticalForce(float verticalForce);
	sf::Vector2u getSizeBounds() const;
    sf::Vector2u getCenter() const;
    sf::IntRect getBoundingBox() const;
    void draw(sf::RenderTarget& target);

    void setState(State s);
    void unsetState(State s);
    bool getState(State s) const;
};

#endif /* CHARACTER_H_ */
