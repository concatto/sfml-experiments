/*
 * Character.cpp
 *
 *  Created on: Jul 4, 2016
 *      Author: concatto
 */

#include "Character.h"

std::vector<Animation> Character::animations{
	Animation(Animation::generateFrames(10, sf::Vector2i(124, 77)), 5)
};


Character::Character(const sf::Texture& texture)
	: sf::Sprite(texture), currentAnimation(nullptr), animationPlaying(false), facingRight(true), movementSpeed(5) {

}

void Character::update() {
	if (animationPlaying) {
		if (currentAnimation != nullptr) {
			currentAnimation->update(*this);
		}
	}
}

void Character::walk() {
	playAnimation(0);
}

void Character::accelerate() {
	Character::animations[0].setUpdateRate(Animation::Fast);
	movementSpeed = Speed::Fast;
}

void Character::slow() {
	Character::animations[0].setUpdateRate(Animation::Normal);
	movementSpeed = Speed::Normal;
}

void Character::moveLeft() {
	if (facingRight) {
		facingRight = false;
		setScale(-1, 1);
		move(124, 0);
	}
	move(-movementSpeed, 0);
}

void Character::moveRight() {
	if (!facingRight) {
		facingRight = true;
		setScale(1, 1);
		move(-124, 0);
	}
	move(movementSpeed, 0);
}

void Character::playAnimation(unsigned int index) {
	currentAnimation = &(Character::animations[index]);
	animationPlaying = true;
	currentAnimation->start();
}
