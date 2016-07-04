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
	enum Speed {Fast = 10, Normal = 2};

	static std::vector<Animation> animations;
	Animation* currentAnimation;
	bool animationPlaying;
	bool facingRight;
	int movementSpeed;

	void playAnimation(unsigned int index);

public:
	Character(const sf::Texture& texture);

	void update();
	void walk();
	void accelerate();
	void slow();
	void moveLeft();
	void moveRight();
};

#endif /* CHARACTER_H_ */
