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
	enum State {Stand = 0, Walk = 1};
	enum Speed {Fast = 10, Normal = 2};

	static std::vector<Animation> animations;
	unsigned int animationIndex;
	bool animationPlaying;
	bool facingRight;
	int movementSpeed;
	sf::IntRect boundingBox;

	void playAnimation(unsigned int index);

public:
	Character(const sf::Texture& texture, sf::IntRect boundingBox);

	void update();
	void accelerate();
	void slow();
	void moveLeft();
	void moveRight();
	void stand();
	bool isFacingRight() const;
	sf::IntRect getBoundingBox() const;
	void draw(sf::RenderTarget& target);
};

#endif /* CHARACTER_H_ */
