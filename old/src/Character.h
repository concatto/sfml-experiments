/*
 * Character.h
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Animation.h"
#include <SFML/Graphics.hpp>

class Character : public sf::Sprite {
private:
	enum State {None = 0, Stand = 1, Walk = 2};
	enum Speed {Fast = 10, Normal = 2};

	static std::vector<Animation> animations;
	sf::Uint32 state;
	unsigned int animationIndex;
	bool animationPlaying;
	bool facingRight;
	int movementSpeed;
	sf::Vector2u sizeBounds;

	void playAnimation(unsigned int index);
	void setState(State s);
	void unsetState(State s);
	bool getState(State s) const;

public:
	Character(const sf::Texture& texture, sf::Vector2u sizeBounds);

	void update();
	void accelerate();
	void slow();
	void moveLeft();
	void moveRight();
	void stand();
	bool isFacingRight() const;
	bool isMoving() const;
	sf::Vector2u getSizeBounds() const;
	void draw(sf::RenderTarget& target);
};

#endif /* CHARACTER_H_ */
